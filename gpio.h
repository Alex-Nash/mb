#ifndef __GPIO_H
#define __GPIO_H

#include "xgpio_l.h"

#define GPIO_CHANNEL 			1

#define BIT_MASK				0x7

void SetGpioToHi(u32 gpioBaseAddress)

void SetGpioToLow(u32 gpioBaseAddress)

#endif
