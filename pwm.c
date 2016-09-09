


void SetPwmGenerator(struct PwmGenerator *pwmGen, u16 power, u16 angle)
{
  u32 dutyCycleA, dutyCycleB, dutyCycleC;
  
  // calculate duty cycle by power and angle
  dutyCycleA = (u32)power * ((u32)APhaseCos(angle) +
          (u32)(0xFFFF - power) * (u32)(0xFFFF >> 2));
  dutyCycleB = (u32)power * ((u32)BPhaseCos(angle) +
          (u32)(0xFFFF - power) * (u32)(0xFFFF >> 2));
  dutyCycleC = (u32)power * ((u32)CPhaseCos(angle) +
          (u32)(0xFFFF - power) * (u32)(0xFFFF >> 2));

  // round duty cycle to u16 and
  // set duty cycle in PWM
  SetPwmDS(pwmGen->APhasePwm, (u16)(dutyCycleA >> 16));
  SetPwmDS(pwmGen->BPhasePwm, (u16)(dutyCycleB >> 16));
  SetPwmDS(pwmGen->CPhasePwm, (u16)(dutyCycleC >> 16));
}

void InitPwmGenerator(struct PwmGenerator *pwmGen,
      u32 tmr1BaseAddr, u32 tmr2BaseAddr, u32 tmr3BaseAddr)
{
  InitPwm(pwmGen->APhasePwm, tmr1BaseAddr);
  InitPwm(pwmGen->BPhasePwm, tmr2BaseAddr);
  InitPwm(pwmGen->CPhasePwm, tmr3BaseAddr);
}

void StartPwm_Generator_Start(struct PwmGenerator *pwmGen)
{
  StartPwm(pwmGen->APhasePwm);
  StartPwm(pwmGen->BPhasePwm);
  StartPwm(pwmGen->CPhasePwm);
}

void StopPwmGenerator(struct PwmGenerator *pwmGen)
{
  StopPwm(pwmGen->APhasePWM);
  StopPwm(pwmGen->BPhasePWM);
  StopPwm(pwmGen->CPhasePWM);
}

void InitPwm(struct Pwm *pwm, u32 TmrCtrBaseAddress)
{
  u32 ControlStatus;

  pwm->TmrCtrBaseAddress = TmrCtrBaseAddress;
	/*
	 * Clear the Control Status Register
	 */
	XTmrCtr_SetControlStatusReg(pwm->TmrCtrBaseAddress, PWM_PERIOD,0x0);
	XTmrCtr_SetControlStatusReg(pwm->TmrCtrBaseAddress, PWM_DUTY,  0x0);

	/*
	 * Config timer in PWM mode
	 */
	XTmrCtr_SetControlStatusReg(pwm->TmrCtrBaseAddress, PWM_PERIOD, XTC_CSR_DOWN_COUNT_MASK | XTC_CSR_EXT_GENERATE_MASK
			| XTC_CSR_AUTO_RELOAD_MASK | XTC_CSR_ENABLE_PWM_MASK);
	XTmrCtr_SetControlStatusReg(pwm->TmrCtrBaseAddress, PWM_DUTY, XTC_CSR_DOWN_COUNT_MASK | XTC_CSR_EXT_GENERATE_MASK
			| XTC_CSR_AUTO_RELOAD_MASK | XTC_CSR_ENABLE_PWM_MASK);

	/*
	 * Set the value that is loaded into the timer counter and cause it to
	 * be loaded into the timer counter
	 */
	XTmrCtr_SetLoadReg(pwm->TmrCtrBaseAddress, PWM_PERIOD, 0xFFFF);
	XTmrCtr_SetLoadReg(pwm->TmrCtrBaseAddress, PWM_DUTY,   0x0000);

	XTmrCtr_LoadTimerCounterReg(pwm->TmrCtrBaseAddress, PWM_PERIOD);
	XTmrCtr_LoadTimerCounterReg(pwm->TmrCtrBaseAddress, PWM_DUTY);

	/*
	 * Clear the Load Timer bit in the Control Status Register
	 */
	ControlStatus = XTmrCtr_GetControlStatusReg(pwm->TmrCtrBaseAddress,
			PWM_PERIOD);
	XTmrCtr_SetControlStatusReg(pwm->TmrCtrBaseAddress, PWM_PERIOD,
				 ControlStatus & (~XTC_CSR_LOAD_MASK));

	ControlStatus = XTmrCtr_GetControlStatusReg(pwm->TmrCtrBaseAddress,
			PWM_DUTY);
	XTmrCtr_SetControlStatusReg(pwm->TmrCtrBaseAddress, PWM_DUTY,
				 ControlStatus & (~XTC_CSR_LOAD_MASK));

}
/*
 * Start the timer counter
 */
void StartPwm(struct Pwm *pwm)
{
  ControlStatus = XTmrCtr_GetControlStatusReg(pwm->TmrCtrBaseAddress,
        PWM_PERIOD);
  XTmrCtr_SetControlStatusReg(pwm->TmrCtrBaseAddress, PWM_PERIOD,
        ControlStatus | XTC_CSR_ENABLE_ALL_MASK);
}
/*
 * Stop the timer counter
 */
void StopPwm(struct Pwm *pwm)
{
  XTmrCtr_Disable(pwm->TmrCtrBaseAddress, PWM_PERIOD);
  XTmrCtr_Disable(pwm->TmrCtrBaseAddress, PWM_DUTY);
}

void SetPwmDS(struct PWM *pwm, u16 dutyCycle )
{
  XTmrCtr_SetLoadReg(pwm->TmrCtrBaseAddress, PWM_DUTY, dutyCycle);
}
