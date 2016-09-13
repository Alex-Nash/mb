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

void InitPwmGenerator(struct PwmGenerator *pwmGen, Encoder *encoder,
    u32 *tmrArray)
{
  u32 sortedTmrArray[3];

  SortPwm(encoder, tmrArray, sortedTmrArray);

  pwmGen->APhasePwmBaseAddress = sortedTmrArray[0];
  pwmGen->BPhasePwmBaseAddress = sortedTmrArray[1];
  pwmGen->CPhasePwmBaseAddress = sortedTmrArray[2];

  InitPwm(pwmGen->APhasePwmBaseAddress);
  InitPwm(pwmGen->BPhasePwmBaseAddress);
  InitPwm(pwmGen->CPhasePwmBaseAddress);
}
/*
* Return sorted timer base address arrey
* where element[0] = A phase timer, element[1] = B phase timer
* element[2] = C phase timer
*/
u32* SortPwm(Encoder *encoder, u32 *tmrArray, u32 *sortedTmrArray)
{
  u32 angle[3];
  int i,j,k;
  for (i = 0; i < 3; i++) {
    InitPwm(tmrArray[i]);
    StartPwm(tmrArray[i]);
    SetPwmDS(tmrArray[i], (u16)(MAX_DS_VALUE >> 1));
    usleep(100); // turn rotor waiting
    angle[i] = GetElectricalAngle(encoder);
    if (angle[i] == ENCODER_ERR)
      return NULL;
    SetPwmDS(tmrArray[i], (u16)(0x00));
    StopPwm(tmrArray[i]);

    // initial define sorded array
    sortedTmrArray[i] = tmrArray[i];
  }
  // Selection sort
  for (i=0; i<3; i++)
  {
    k=i;
    for (j=i+1; j<3; j++)
      if (less(angle[j], angle[k]))
        k=j;
    if (i!=k)
    {
      swap(angle[i], angle[k]);
      swap(sortedTmrArray[i], sortedTmrArray[k]);
    }
  }

  return sortedTmrArray;
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
