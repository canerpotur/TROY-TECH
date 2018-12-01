#include "GPSX.h"

// **** PIN ASSIGNMENT ****
// All lines are shared between two controllers except for ATT1 and ATT2.
// "Data" and "ACK" are open drain and require a pull-up resister of
// 1k ohms for PS2. For PS1, simply set the pin to high-impedance to use
// internal resister.
// Other pins can connect directly to the MPU.
//
// Arduino Pin No.   PSX Controller Pin No.
// ---------------------------------------
#define DAT_PIN 7 // CTL1 Data
#define CMD_PIN 6 // CTL2 Command
                  // CTL3 9V for Motor (Optional)
                  // CTL4 GND
                  // CTL5 VCC
#define AT1_PIN 5 // CTL6 Attention (PAD1)
#define CLK_PIN 4 // CTL7 Clock
                  // CTL8 N/C
#define ACK_PIN 3 // CTL9 ACK

#define AT2_PIN 2 // CTL6 Attention (PAD2)


// Various delays. May require adjustment.
// Values are for {PS1, PS2} which are each designed to run at 250/500kHz
static unsigned char wait_after_att[]    = { 50, 15};   // nsec
static unsigned char command_interval[]  = { 16, 10};   // msec
static unsigned char clk_half_cycle[]    = {  2,  1};   // nsec
static unsigned char ack_wait_duration[] = {15,  15};   // nsec
static unsigned char pin_impedance[]     = {HIGH, HIGH};


// Variables
static unsigned char psx_type;
static unsigned char *pad_state;


// Functions
static unsigned char psx_read_write_byte(unsigned char cmd_byte);


void psx_init (unsigned char type)
{
	psx_type = type;

	//Pin I/O direction
	pinMode(CLK_PIN, OUTPUT);
	pinMode(CMD_PIN, OUTPUT);

	pinMode(DAT_PIN, INPUT);
	pinMode(AT1_PIN, OUTPUT);
	pinMode(AT2_PIN, OUTPUT);
	pinMode(ACK_PIN, INPUT);

	//Pin initial state
	digitalWrite(CLK_PIN, HIGH);
	digitalWrite(CMD_PIN, LOW);
	digitalWrite(AT1_PIN, HIGH);
	digitalWrite(AT2_PIN, HIGH);

	digitalWrite(DAT_PIN, pin_impedance[psx_type]);
	digitalWrite(ACK_PIN, pin_impedance[psx_type]);
	if (!pad_state)
		pad_state = (unsigned char *)calloc(PAD_BUFFER_SIZE, sizeof(unsigned char));
}


void psx_cmd (unsigned char pad_no,
              const unsigned char * msg,
              unsigned char msg_cnt,
              unsigned char ** key_state,
              unsigned char * byte_cnt)
{
	unsigned char state_buffer_ptr = 0;
	unsigned char att_pin = (pad_no == PSX_PAD1) ? AT1_PIN : AT2_PIN;

	// Get attention
	digitalWrite(att_pin, LOW);
	delayMicroseconds( wait_after_att[psx_type] );

	unsigned char cmd;

	while (state_buffer_ptr < 9) {
		cmd = (state_buffer_ptr < msg_cnt) ? msg[state_buffer_ptr] : 0x00;
		pad_state[state_buffer_ptr] = psx_read_write_byte(cmd);
		delayMicroseconds( ack_wait_duration[psx_type] );
		if (state_buffer_ptr++ > PAD_BUFFER_SIZE)
			break;
	}

	digitalWrite(att_pin, HIGH);
	delay( command_interval[psx_type] );

	*key_state = pad_state;
	*byte_cnt  = state_buffer_ptr;
}


static unsigned char psx_read_write_byte (unsigned char cmd_byte)
{
	int i = 0;
	unsigned char received = 0;

	for (i = 0; i < 8; i++) {
		digitalWrite(CMD_PIN, cmd_byte & 0x01);
		cmd_byte >>= 1;

		//Clock Down
		digitalWrite(CLK_PIN, LOW);
		delayMicroseconds( clk_half_cycle[psx_type] );

		//Clock Up
		digitalWrite(CLK_PIN, HIGH);
		delayMicroseconds( clk_half_cycle[psx_type] );

		received >>= 1;
		if (digitalRead(DAT_PIN))
			received |= 0x80;
	}
	return received;
}
