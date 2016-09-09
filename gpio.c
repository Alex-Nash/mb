
#include "gpio.h"

void SetGpioToHi(u32 gpioBaseAddress)
{
	/* Set the direction for all 3 bit -out- */
	XGpio_WriteReg(gpioBaseAddress,
      ((GPIO_CHANNEL - 1) * XGPIO_CHAN_OFFSET) +
      XGPIO_TRI_OFFSET, BIT_MASK);

	/* Set the data for all 3 bit*/
	XGpio_WriteReg(gpioBaseAddress,
      ((GPIO_CHANNEL - 1) * XGPIO_CHAN_OFFSET) +
			XGPIO_DATA_OFFSET, BIT_MASK);
}

void SetGpioToLow(u32 gpioBaseAddress)
{
	/* Set the direction for all 3 bit -out- */
	XGpio_WriteReg(gpioBaseAddress,
      ((GPIO_CHANNEL - 1) * XGPIO_CHAN_OFFSET) +
			XGPIO_TRI_OFFSET, BIT_MASK);

	/* Set the data for all 3 bit */
	XGpio_WriteReg(gpioBaseAddress,
      ((GPIO_CHANNEL - 1) * XGPIO_CHAN_OFFSET) +
      XGPIO_DATA_OFFSET, ~BIT_MASK);
}
