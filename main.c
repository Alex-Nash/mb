#define TMR0_1_BASE_ADDRESS     XPAR_TIMER0A_BASEADDR
#define TMR0_2_BASE_ADDRESS     XPAR_TIMER0B_BASEADDR
#define TMR0_3_BASE_ADDRESS     XPAR_TIMER0C_BASEADDR
#define GPIO0_BASE_ADDRESS      XPAR_GPIO0PWM_BASEADDR
#define ENCODER0_DEVICE_ID      XPAR_SPI0_DEVICE_ID

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "gpio.h"
#include "engine.h"
#include "encoder.h"
#include "pwm.h"



int main()
{
	  SetCosArray();
	  struct Engine leftEngine;
	  struct PwmGenerator pwmGen;
		Encoder encoder;
		u32 timerArray[3];
		timerArray[0] = (u32)TMR0_1_BASE_ADDRESS;
		timerArray[1] = (u32)TMR0_2_BASE_ADDRESS;
		timerArray[2] = (u32)TMR0_3_BASE_ADDRESS);

	  InitPwmGenerator(&pwmGen, &timerArray);

		InitEncoder(&encoder, ENCODER0_DEVICE_ID);

	  InitEngine(&leftEngine, &pwmGen, &encoder, GPIO0_BASE_ADDRESS);

	  StartForward(&leftEngine, 0x2FFF, 8);
    return 0;
}
