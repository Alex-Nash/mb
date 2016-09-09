#ifndef __PWM_H
#define __PWM_H

#include "xparameters.h"
#include "xstatus.h"
#include "xtmrctr_l.h"

#define PWM_PERIOD            0
#define PWM_DUTY              1
#define PWM_MAX_DUTY_VALUE    0xFFFF

struct PwmGenerator
{
  u32 APhasePwmBaseAddress;
  u32 BPhasePwmBaseAddress;
  u32 CPhasePwmBaseAddress;
};


void SetPwmGenerator(struct PwmGenerator *pwmGen, u16 angle);

void InitPwmGenerator(struct PwmGenerator *pwmGen,
    u32 tmr1BaseAddr, u32 tmr2BaseAddr, u32 tmr3BaseAddr);

void StartPwmGenerator(struct PwmGenerator *pwmGen);

void StopPwmGenerator(struct PwmGenerator *pwmGen);

void InitPwm(struct Pwm *pwm);

void StartPwm(struct Pwm *pwm);

void StopPwm(struct Pwm *pwm);

void SetPwmDS(struct PWM *pwm, u16 dutyCycle);

#endif
