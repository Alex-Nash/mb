#define TMR0_1_BASE_ADDRESS     XPAR_TIMER0A_BASEADDR
#define TMR0_2_BASE_ADDRESS     XPAR_TIMER0B_BASEADDR
#define TMR0_3_BASE_ADDRESS     XPAR_TIMER0C_BASEADDR
#define GPIO0_BASE_ADDRESS      XPAR_GPIO0PWM_BASEADDR
#define ENCODER0_DEVICE_ID      XPAR_SPI0_DEVICE_ID
#define GPIO					0x0000
#define DASH_BOARD_BASE_ADDRESS	0x80000100

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "gpio.h"
#include "engine.h"
#include "encoder.h"
#include "pwm.h"



int main()
{

	struct Engine leftEngine;
	struct PwmGenerator pwmGen;
	struct Encoder encoder;
	struct Command command;
	u32 timerArray[3];
	timerArray[0] = (u32)TMR0_1_BASE_ADDRESS;
	timerArray[1] = (u32)TMR0_2_BASE_ADDRESS;
	timerArray[2] = (u32)TMR0_3_BASE_ADDRESS;

	XSpi spi;
	InitEncoder(&encoder, &spi, ENCODER0_DEVICE_ID, GPIO);

	InitPwmGenerator(&pwmGen, &encoder, timerArray);

	InitCommand(&command, DASH_BOARD_BASE_ADDRESS);

	InitEngine(&leftEngine, &pwmGen, &encoder,
				GPIO0_BASE_ADDRESS, ENG_POSITION_LEFT);


    return 0;
}
