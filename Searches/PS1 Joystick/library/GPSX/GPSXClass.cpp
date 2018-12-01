#include "GPSXClass.h"

#define MOTOR1_LEVEL_BYTE  cmd_poll[3]
#define MOTOR2_LEVEL_BYTE  cmd_poll[4]

#define MOTOR1_ENABLE_BYTE cmd_enable_motor[3]
#define MOTOR2_ENABLE_BYTE cmd_enable_motor[4]

#define AD_MODE_BYTE       cmd_ad_mode[3]
#define AD_MODE_LOCK_BYTE  cmd_ad_mode[4]


#define STATE_CURRENT  0
#define STATE_PREVIOUS 1


// Command bytes.
// When the lines contain values, the array is reused by modifying values on the fly.

//static unsigned char cmd_init[]         = {0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static unsigned char cmd_poll[]         = {0x01, 0x42, 0x00, 0x00, 0x00};
static unsigned char cmd_enter_cfg[]    = {0x01, 0x43, 0x00, 0x01};
static unsigned char cmd_exit_cfg[]     = {0x01, 0x43, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A};
static unsigned char cmd_enable_motor[] = {0x01, 0x4D, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static unsigned char cmd_ad_mode[]      = {0x01, 0x44, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};


// Levels of the motors.
// This is necessary to store separately as the "state poll" command may over ride
// the motor strength with values of the other one of the two pads.
static unsigned char motor1Level[] = {MOTOR1_OFF, MOTOR1_OFF};
static unsigned char motor2Level[] = {0x00, 0x00};


// 2 key states states (current & previous) for 2 controllers.
unsigned char *keyState[2][2];
static unsigned char byte_cnt[2];


GPSXClass::GPSXClass(unsigned char psType)
{
	psx_init(psType);

	unsigned int i, j;

	for (i=0; i < 2; i++)
		for (j=0; j < 2; j++)
			keyState[i][j] = (unsigned char *)calloc(sizeof(unsigned char), PAD_BUFFER_SIZE);
}

/* Probably deprecated
void GPSXClass::init(unsigned char padNo)
{
	unsigned char *tmp;
	psx_cmd(padNo, cmd_init, sizeof(cmd_init), &tmp, &byte_cnt[padNo]);
	for (int i=0; i<byte_cnt[padNo]; i++)
		keyState[padNo][STATE_CURRENT][i] = tmp[i];
}
*/

void GPSXClass::updateState(unsigned char padNo)
{
	// Swap pointer
	unsigned char *tmp = keyState[padNo][STATE_CURRENT];
	keyState[padNo][STATE_CURRENT]  = keyState[padNo][STATE_PREVIOUS];
	keyState[padNo][STATE_PREVIOUS] = tmp;

	// Set motor value
	MOTOR1_LEVEL_BYTE = motor1Level[padNo];
	MOTOR2_LEVEL_BYTE = motor2Level[padNo];

	psx_cmd(padNo, cmd_poll, sizeof(cmd_poll), &tmp, &byte_cnt[padNo]);
	for (int i=0; i<byte_cnt[padNo]; i++)
		keyState[padNo][STATE_CURRENT][i] = tmp[i];

	// For digital keys, previous state is stored as a mask (XOR)
	// of bits changed from previous poll.
	keyState[padNo][STATE_PREVIOUS][3] ^= keyState[padNo][STATE_CURRENT][3];
	keyState[padNo][STATE_PREVIOUS][4] ^= keyState[padNo][STATE_CURRENT][4];
}


void GPSXClass::motor(unsigned char padNo,
					  unsigned char motor1OnOff,
					  unsigned char motor2Value)
{
	motor1Level[padNo] = motor1OnOff;
	motor2Level[padNo] = motor2Value;
}


void GPSXClass::mode(unsigned char padNo, unsigned char mode, unsigned char lock)
{
	AD_MODE_BYTE      = mode;
	AD_MODE_LOCK_BYTE = lock;

	unsigned char *state;
	unsigned char cnt;
	psx_cmd(padNo, cmd_enter_cfg, sizeof(cmd_enter_cfg), &state, &cnt);
	psx_cmd(padNo, cmd_ad_mode, sizeof(cmd_ad_mode), &state, &cnt);
	psx_cmd(padNo, cmd_exit_cfg, sizeof(cmd_exit_cfg), &state, &cnt);
}


void GPSXClass::motorEnable(unsigned char padNo,
							unsigned char motor1Enable,
							unsigned char motor2Enable)
{
	MOTOR1_ENABLE_BYTE = motor1Enable;
	MOTOR2_ENABLE_BYTE = motor2Enable;

	unsigned char *state;
	unsigned char cnt;
	psx_cmd(padNo, cmd_enter_cfg, sizeof(cmd_enter_cfg), &state, &cnt);
	psx_cmd(padNo, cmd_enable_motor, sizeof(cmd_enable_motor), &state, &cnt);
	psx_cmd(padNo, cmd_exit_cfg, sizeof(cmd_exit_cfg), &state, &cnt);
}

/* Probably Deprecate
void GPSXClass::getResponse(unsigned char padNo,
							unsigned char **pstate,
							unsigned char *bytes)
{
	*pstate = keyState[padNo][STATE_CURRENT];
	*bytes = byte_cnt[padNo];
}
*/

GPSXClass PSX = GPSXClass(PS2);
