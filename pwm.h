#ifndef __PWM_H
#define __PWM_H

#include "xparameters.h"
#include "xstatus.h"
#include "xtmrctr_l.h"

#define PWM_PERIOD  0
#define PWM_DUTY    1

struct PwmGenerator
{
  struct Pwm *APhasePwm;
  struct Pwm *BPhasePwm;
  struct Pwm *CPhasePwm;
};

struct Pwm
{
  u32 TmrCtrBaseAddress;
};

void SetPwmGenerator(struct PwmGenerator *pwmGen, u16 angle);

void InitPwmGenerator(struct PwmGenerator *pwmGen);

void StartPwm_Generator_Start(struct PwmGenerator *pwmGen);

void StopPwmGenerator(struct PwmGenerator *pwmGen);

void InitPwm(struct Pwm *pwm);

void StartPwm(struct Pwm *pwm);

void StopPwm(struct Pwm *pwm);

void SetPwmDS(struct PWM *pwm, u16 dutyCycle);

#endif
