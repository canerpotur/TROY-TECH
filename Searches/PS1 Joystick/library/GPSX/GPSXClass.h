// All of the low level work is done in GPSX.(c|h)


#ifndef _GPSXCLASS_H
#define _GPSXCLASS_H

#include "GPSX.h"


// Macros to enable/disable the two motors in DualShock pads

#define MOTOR1_ENABLE  0x00
#define MOTOR1_DISABLE 0xFF

#define MOTOR2_ENABLE  0x01
#define MOTOR2_DISABLE 0xFF


// Macros to control motor1
// (unlike motor2 with variable steps, motor1 has only on/off state)

#define MOTOR1_ON  0xFF
#define MOTOR1_OFF 0x00


// Macros to select A/D pad modes

#define MODE_DIGITAL 0x00
#define MODE_ANALOG  0x01


// Macros to lock / unlock A/D pad modes

#define MODE_LOCK    0x03
#define MODE_UNLOCK  0x02


// Here are your funcions
class GPSXClass
{
	public:
		GPSXClass(unsigned char psType);
//		void init(unsigned char padNo);   Probably deprecated
		void updateState(unsigned char padNo);
		void motorEnable(unsigned char padNo, unsigned char motor1OnOff, unsigned char motor2OnOff);
		void motor(unsigned char padNo, unsigned char motor1OnOff, unsigned char motor2Level);
		void mode(unsigned char padNo, unsigned char mode, unsigned char lock);

//		void getResponse(unsigned char padNo, unsigned char **pstate, unsigned char *bytes); Probably deprecated
};


#define STATE_CURRENT  0
#define STATE_PREVIOUS 1


// Macros to ease checking changes in key state.
// x = pad number (PSX_PAD1 or PSX_PAD2)

#define IS_DOWN_LEFT(x)        ( !(keyState[(x)][STATE_CURRENT][3] & (1<<7)) )
#define IS_DOWN_DOWN(x)        ( !(keyState[(x)][STATE_CURRENT][3] & (1<<6)) )
#define IS_DOWN_RIGHT(x)       ( !(keyState[(x)][STATE_CURRENT][3] & (1<<5)) )
#define IS_DOWN_UP(x)          ( !(keyState[(x)][STATE_CURRENT][3] & (1<<4)) )
#define IS_DOWN_START(x)       ( !(keyState[(x)][STATE_CURRENT][3] & (1<<3)) )
#define IS_DOWN_STICK_RIGHT(x) ( !(keyState[(x)][STATE_CURRENT][3] & (1<<2)) )
#define IS_DOWN_STICK_LEFT(x)  ( !(keyState[(x)][STATE_CURRENT][3] & (1<<1)) )
#define IS_DOWN_SELECT(x)      ( !(keyState[(x)][STATE_CURRENT][3] & 1) )

#define IS_DOWN_SQUARE(x)      ( !(keyState[(x)][STATE_CURRENT][4] & (1<<7)) )
#define IS_DOWN_CROSS(x)       ( !(keyState[(x)][STATE_CURRENT][4] & (1<<6)) )
#define IS_DOWN_CIRCLE(x)      ( !(keyState[(x)][STATE_CURRENT][4] & (1<<5)) )
#define IS_DOWN_TRIANGLE(x)    ( !(keyState[(x)][STATE_CURRENT][4] & (1<<4)) )
#define IS_DOWN_R1(x)          ( !(keyState[(x)][STATE_CURRENT][4] & (1<<3)) )
#define IS_DOWN_L1(x)          ( !(keyState[(x)][STATE_CURRENT][4] & (1<<2)) )
#define IS_DOWN_R2(x)          ( !(keyState[(x)][STATE_CURRENT][4] & (1<<1)) )
#define IS_DOWN_L2(x)          ( !(keyState[(x)][STATE_CURRENT][4] & 1) )


#define PRESSED_LEFT(x)        ( (keyState[(x)][STATE_PREVIOUS][3] & (1<<7))  &&  !(keyState[(x)][STATE_CURRENT][3] & (1<<7)) )
#define PRESSED_DOWN(x)        ( (keyState[(x)][STATE_PREVIOUS][3] & (1<<6))  &&  !(keyState[(x)][STATE_CURRENT][3] & (1<<6)) )
#define PRESSED_RIGHT(x)       ( (keyState[(x)][STATE_PREVIOUS][3] & (1<<5))  &&  !(keyState[(x)][STATE_CURRENT][3] & (1<<5)) )
#define PRESSED_UP(x)          ( (keyState[(x)][STATE_PREVIOUS][3] & (1<<4))  &&  !(keyState[(x)][STATE_CURRENT][3] & (1<<4)) )
#define PRESSED_START(x)       ( (keyState[(x)][STATE_PREVIOUS][3] & (1<<3))  &&  !(keyState[(x)][STATE_CURRENT][3] & (1<<3)) )
#define PRESSED_STICK_RIGHT(x) ( (keyState[(x)][STATE_PREVIOUS][3] & (1<<2))  &&  !(keyState[(x)][STATE_CURRENT][3] & (1<<2)) )
#define PRESSED_STICK_LEFT(x)  ( (keyState[(x)][STATE_PREVIOUS][3] & (1<<1))  &&  !(keyState[(x)][STATE_CURRENT][3] & (1<<1)) )
#define PRESSED_SELECT(x)      ( (keyState[(x)][STATE_PREVIOUS][3] & 1)       &&  !(keyState[(x)][STATE_CURRENT][3] & 1) )

#define PRESSED_SQUARE(x)      ( (keyState[(x)][STATE_PREVIOUS][4] & (1<<7))  &&  !(keyState[(x)][STATE_CURRENT][4] & (1<<7)) )
#define PRESSED_CROSS(x)       ( (keyState[(x)][STATE_PREVIOUS][4] & (1<<6))  &&  !(keyState[(x)][STATE_CURRENT][4] & (1<<6)) )
#define PRESSED_CIRCLE(x)      ( (keyState[(x)][STATE_PREVIOUS][4] & (1<<5))  &&  !(keyState[(x)][STATE_CURRENT][4] & (1<<5)) )
#define PRESSED_TRIANGLE(x)    ( (keyState[(x)][STATE_PREVIOUS][4] & (1<<4))  &&  !(keyState[(x)][STATE_CURRENT][4] & (1<<4)) )
#define PRESSED_R1(x)          ( (keyState[(x)][STATE_PREVIOUS][4] & (1<<3))  &&  !(keyState[(x)][STATE_CURRENT][4] & (1<<3)) )
#define PRESSED_L1(x)          ( (keyState[(x)][STATE_PREVIOUS][4] & (1<<2))  &&  !(keyState[(x)][STATE_CURRENT][4] & (1<<2)) )
#define PRESSED_R2(x)          ( (keyState[(x)][STATE_PREVIOUS][4] & (1<<1))  &&  !(keyState[(x)][STATE_CURRENT][4] & (1<<1)) )
#define PRESSED_L2(x)          ( (keyState[(x)][STATE_PREVIOUS][4] & 1)       &&  !(keyState[(x)][STATE_CURRENT][4] & 1) )


#define RELEASED_LEFT(x)        ( (keyState[(x)][STATE_PREVIOUS][3] & (1<<7))  &&  (keyState[(x)][STATE_CURRENT][3] & (1<<7)) )
#define RELEASED_DOWN(x)        ( (keyState[(x)][STATE_PREVIOUS][3] & (1<<6))  &&  (keyState[(x)][STATE_CURRENT][3] & (1<<6)) )
#define RELEASED_RIGHT(x)       ( (keyState[(x)][STATE_PREVIOUS][3] & (1<<5))  &&  (keyState[(x)][STATE_CURRENT][3] & (1<<5)) )
#define RELEASED_UP(x)          ( (keyState[(x)][STATE_PREVIOUS][3] & (1<<4))  &&  (keyState[(x)][STATE_CURRENT][3] & (1<<4)) )
#define RELEASED_START(x)       ( (keyState[(x)][STATE_PREVIOUS][3] & (1<<3))  &&  (keyState[(x)][STATE_CURRENT][3] & (1<<3)) )
#define RELEASED_STICK_RIGHT(x) ( (keyState[(x)][STATE_PREVIOUS][3] & (1<<2))  &&  (keyState[(x)][STATE_CURRENT][3] & (1<<2)) )
#define RELEASED_STICK_LEFT(x)  ( (keyState[(x)][STATE_PREVIOUS][3] & (1<<1))  &&  (keyState[(x)][STATE_CURRENT][3] & (1<<1)) )
#define RELEASED_SELECT(x)      ( (keyState[(x)][STATE_PREVIOUS][3] & 1)       &&  (keyState[(x)][STATE_CURRENT][3] & 1) )

#define RELEASED_SQUARE(x)      ( (keyState[(x)][STATE_PREVIOUS][4] & (1<<7))  &&  (keyState[(x)][STATE_CURRENT][4] & (1<<7)) )
#define RELEASED_CROSS(x)       ( (keyState[(x)][STATE_PREVIOUS][4] & (1<<6))  &&  (keyState[(x)][STATE_CURRENT][4] & (1<<6)) )
#define RELEASED_CIRCLE(x)      ( (keyState[(x)][STATE_PREVIOUS][4] & (1<<5))  &&  (keyState[(x)][STATE_CURRENT][4] & (1<<5)) )
#define RELEASED_TRIANGLE(x)    ( (keyState[(x)][STATE_PREVIOUS][4] & (1<<4))  &&  (keyState[(x)][STATE_CURRENT][4] & (1<<4)) )
#define RELEASED_R1(x)          ( (keyState[(x)][STATE_PREVIOUS][4] & (1<<3))  &&  (keyState[(x)][STATE_CURRENT][4] & (1<<3)) )
#define RELEASED_L1(x)          ( (keyState[(x)][STATE_PREVIOUS][4] & (1<<2))  &&  (keyState[(x)][STATE_CURRENT][4] & (1<<2)) )
#define RELEASED_R2(x)          ( (keyState[(x)][STATE_PREVIOUS][4] & (1<<1))  &&  (keyState[(x)][STATE_CURRENT][4] & (1<<1)) )
#define RELEASED_L2(x)          ( (keyState[(x)][STATE_PREVIOUS][4] & 1)       &&  (keyState[(x)][STATE_CURRENT][4] & 1) )


#define ANALOG_RIGHT_X(x) (keyState[(x)][STATE_CURRENT][5])
#define ANALOG_RIGHT_Y(x) (keyState[(x)][STATE_CURRENT][6])
#define ANALOG_LEFT_X(x)  (keyState[(x)][STATE_CURRENT][7])
#define ANALOG_LEFT_Y(x)  (keyState[(x)][STATE_CURRENT][8])


//**************** Stuff you don't need to worry about  ****************

extern unsigned char *keyState[2][2];
extern GPSXClass PSX;

#endif // _GPSXCLASS_H
