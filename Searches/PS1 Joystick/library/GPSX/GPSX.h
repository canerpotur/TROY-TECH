#ifndef _GPSX_H
#define _GPSX_H

#include <stdlib.h>
#include <wiring_private.h>

//Maximum bytes to receive per request.
#define PAD_BUFFER_SIZE 20

#define	PSX_PAD1 0
#define	PSX_PAD2 1

#define ACK_OK 0x01
#define ACK_NG 0x00

#define PS1 0
#define PS2 1

#define IS_ANALOG(x)       (((x)[1] & 0xF0) == 0x40)
#define IS_DIGITAL(x)      (((x)[1] & 0xF0) == 0x70)

#define ANALOG_RIGHT_X_STATE(x)  ((x)[5])
#define ANALOG_RIGHT_Y_STATE(x)  ((x)[6])
#define ANALOG_LEFT_X_STATE(x)   ((x)[7])
#define ANALOG_LEFT_Y_STATE(x)   ((x)[8])

#define BTN_LEFT(x)        (!((x)[3] & (1<<7)))
#define BTN_DOWN(x)        (!((x)[3] & (1<<6)))
#define BTN_RIGHT(x)       (!((x)[3] & (1<<5)))
#define BTN_UP(x)          (!((x)[3] & (1<<4)))
#define BTN_START(x)       (!((x)[3] & (1<<3)))
#define BTN_STICK_RIGHT(x) (!((x)[3] & (1<<2)))
#define BTN_STICK_LEFT(x)  (!((x)[3] & (1<<1)))
#define BTN_SELECT(x)      (!((x)[3] & 1))

#define BTN_SQUARE(x)      (!((x)[4] & (1<<7)))
#define BTN_CROSS(x)       (!((x)[4] & (1<<6)))
#define BTN_CIRCLE(x)      (!((x)[4] & (1<<5)))
#define BTN_TRIANGLE(x)    (!((x)[4] & (1<<4)))
#define BTN_R1(x)          (!((x)[4] & (1<<3)))
#define BTN_L1(x)          (!((x)[4] & (1<<2)))
#define BTN_R2(x)          (!((x)[4] & (1<<1)))
#define BTN_L2(x)          (!((x)[4] & 1))


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void psx_init(unsigned char type);
void psx_cmd(unsigned char pad_no, 
             const unsigned char * msg,
			 unsigned char msg_cnt,
             unsigned char ** key_state,
             unsigned char * byte_cnt);


#ifdef __cplusplus
}
#endif // __cplusplus


#endif //_GPSX_H
