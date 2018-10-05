#ifndef _COMMON_H_
#define _COMMON_H_

typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;
typedef short int16_t;
typedef unsigned int uint32_t;
typedef int int32_t;

#define FALSE 0
#define TRUE 1

#define GET_BIT(value, index)   (((value) >> (index)) & 1)

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);

#endif
