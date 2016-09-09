

#define TMR0_1_BASE_ADDRESS     XPAR_TIMER0A_BASEADDR
#define TMR0_2_BASE_ADDRESS     XPAR_TIMER0B_BASEADDR
#define TMR0_3_BASE_ADDRESS     XPAR_TIMER0C_BASEADDR
#define GPIO0_BASE_ADDRESS      XPAR_GPIO0PWM_BASEADDR
#define ENCODER0_DEVICE_ID      XPAR_SPI0_DEVISE_ID


int main(void)
{
  SetCosArray();
  struct Engine leftEngine;
  struct PWM_Generator pwmGen;

  InitPwmGenerator(pwmGen,  TMR0_1_BASE_ADDRESS,
                            TMR0_2_BASE_ADDRESS,
                            TMR0_3_BASE_ADDRESS);

  InitEngine(leftEngine, pwmGen, ENCODER0_DEVICE_ID, GPIO0_BASE_ADDRESS);

  StartForward(leftEngine, 0x2FFF, 8);



}
