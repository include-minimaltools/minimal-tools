#include <bios.h>

 /* Ports */ 

#define COM1  0
#define COM2  1
#define COM3  2
#define COM4  3

/* some HandSk Signal */
   
#define DATA_READY   0x100
#define OVERRUN_ERR  0x200
#define PARITY_ERR   0x400
#define FRAME_ERR    0x800

#define BREAK_DONE   0x1000
#define HOLD_EMPTY   0x2000
#define SHIFT_EMPTY  0x4000
#define TIME_OUT     0x8000

/* ---------------------- */

#define CHGE_CLR2S   0x1
#define CHGE_DS_RDY  0x2  
#define TRAIL_ERING  0x4  
#define CHGE_RX_LIN  0x8  

#define CLR_2_SEND   0x10  
#define DATA_SET_RDY 0x20  
#define RING_IND     0x40  
#define RX_LINE      0x80  

/* Commands      */

#define CONFIG  0
#define WRITE   1
#define READ    2
#define STATUS  3


/*  Comm Parameters: n Bits, stop Bits, Parity, Baud Rate */

#define BITS_7        0x02
#define BITS_8        0x03

#define STOP_BIT_1    0x00
#define STOP_BIT_2    0x04

#define PARITY_NONE   0x00
#define PARITY_ODD    0x08
#define PARITY_EVEN   0x18

#define BAUD_110      0x00
#define BAUD_150      0x20
#define BAUD_300      0x40
#define BAUD_600      0x60
#define BAUD_1200     0x80
#define BAUD_2400     0xA0
#define BAUD_4800     0xC0
#define BAUD_9600     0xE0
