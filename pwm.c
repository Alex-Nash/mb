// Set tree phase of PWM genegator
#include "pwm.h"

void SetPwmGenerator(struct PwmGenerator *pwmGen, u16 power, u16 angle)
{
  u32 dutyCycleA, dutyCycleB, dutyCycleC;

  // calculate duty cycle by power and angle
  dutyCycleA = (u32)power * ((u32)APhaseCos(angle)
      + (u32)(PWM_MAX_DUTY_VALUE - power) * (u32)(PWM_MAX_DUTY_VALUE >> 1));
  dutyCycleB = (u32)power * ((u32)BPhaseCos(angle)
      + (u32)(PWM_MAX_DUTY_VALUE - power) * (u32)(PWM_MAX_DUTY_VALUE >> 1));
  dutyCycleC = (u32)power * ((u32)CPhaseCos(angle)
      + (u32)(PWM_MAX_DUTY_VALUE - power) * (u32)(PWM_MAX_DUTY_VALUE >> 1));

  // round duty cycle to u16 and
  // set duty cycle in PWM
  SetPwmDS(pwmGen->APhasePwmBaseAddress, (u16)(dutyCycleA >> 16));
  SetPwmDS(pwmGen->BPhasePwmBaseAddress, (u16)(dutyCycleB >> 16));
  SetPwmDS(pwmGen->CPhasePwmBaseAddress, (u16)(dutyCycleC >> 16));
}

void InitPwmGenerator(struct PwmGenerator *pwmGen,
    u32 tmr1BaseAddr, u32 tmr2BaseAddr, u32 tmr3BaseAddr)
{
  pwmGen->APhasePwmBaseAddress = tmr2BaseAddr;
  pwmGen->BPhasePwmBaseAddress = tmr2BaseAddr;
  pwmGen->CPhasePwmBaseAddress = tmr2BaseAddr;
  InitPwm(pwmGen->APhasePwmBaseAddress);
  InitPwm(pwmGen->BPhasePwmBaseAddress);
  InitPwm(pwmGen->CPhasePwmBaseAddress);
}

void StartPwmGenerator(struct PwmGenerator *pwmGen)
{
  StartPwm(pwmGen->APhasePwmBaseAddress);
  StartPwm(pwmGen->BPhasePwmBaseAddress);
  StartPwm(pwmGen->CPhasePwmBaseAddress);
}

void StopPwmGenerator(struct PwmGenerator *pwmGen)
{
  StopPwm(pwmGen->APhasePwmBaseAddress);
  StopPwm(pwmGen->BPhasePwmBaseAddress);
  StopPwm(pwmGen->CPhasePwmBaseAddress);
}

void InitPwm(u32 TmrCtrBaseAddress)
{
  u32 ControlStatus;

	/*
	 * Clear the Control Status Register
	 */
	XTmrCtr_SetControlStatusReg(TmrCtrBaseAddress, PWM_PERIOD,0x0);
	XTmrCtr_SetControlStatusReg(TmrCtrBaseAddress, PWM_DUTY,  0x0);

	/*
	 * Config timer in PWM mode
	 */
	XTmrCtr_SetControlStatusReg(TmrCtrBaseAddress, PWM_PERIOD, XTC_CSR_DOWN_COUNT_MASK
      | XTC_CSR_EXT_GENERATE_MASK	| XTC_CSR_AUTO_RELOAD_MASK | XTC_CSR_ENABLE_PWM_MASK);
	XTmrCtr_SetControlStatusReg(TmrCtrBaseAddress, PWM_DUTY, XTC_CSR_DOWN_COUNT_MASK
      | XTC_CSR_EXT_GENERATE_MASK	| XTC_CSR_AUTO_RELOAD_MASK | XTC_CSR_ENABLE_PWM_MASK);

	/*
	 * Set the value that is loaded into the timer counter and cause it to
	 * be loaded into the timer counter
	 */
	XTmrCtr_SetLoadReg(TmrCtrBaseAddress, PWM_PERIOD, 0xFFFF);
	XTmrCtr_SetLoadReg(TmrCtrBaseAddress, PWM_DUTY,   0x0000);

	XTmrCtr_LoadTimerCounterReg(TmrCtrBaseAddress, PWM_PERIOD);
	XTmrCtr_LoadTimerCounterReg(TmrCtrBaseAddress, PWM_DUTY);

	/*
	 * Clear the Load Timer bit in the Control Status Register
	 */
	ControlStatus = XTmrCtr_GetControlStatusReg(TmrCtrBaseAddress,
	    PWM_PERIOD);
	XTmrCtr_SetControlStatusReg(TmrCtrBaseAddress, PWM_PERIOD,
	    ControlStatus & (~XTC_CSR_LOAD_MASK));

	ControlStatus = XTmrCtr_GetControlStatusReg(TmrCtrBaseAddress,
      PWM_DUTY);
	XTmrCtr_SetControlStatusReg(TmrCtrBaseAddress, PWM_DUTY,
	    ControlStatus & (~XTC_CSR_LOAD_MASK));

}
/*
 * Start the timer counter
 */
void StartPwm(u32 TmrCtrBaseAddress)
{
  u32 ControlStatus;
  ControlStatus = XTmrCtr_GetControlStatusReg(TmrCtrBaseAddress,
      PWM_PERIOD);
  XTmrCtr_SetControlStatusReg(TmrCtrBaseAddress, PWM_PERIOD,
      ControlStatus | XTC_CSR_ENABLE_ALL_MASK);
}
/*
 * Stop the timer counter
 */
void StopPwm(u32 TmrCtrBaseAddress)
{
  XTmrCtr_Disable(TmrCtrBaseAddress, PWM_PERIOD);
  XTmrCtr_Disable(TmrCtrBaseAddress, PWM_DUTY);
}

/*
 * Set Load register timer 1 counter (duty cycle)
 */
void SetPwmDS(u32 TmrCtrBaseAddress, u16 dutyCycle )
{
  XTmrCtr_SetLoadReg(TmrCtrBaseAddress, PWM_DUTY, dutyCycle);
}
