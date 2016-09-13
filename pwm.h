#ifndef __PWM_H
#define __PWM_H

#include "sincos.h"
#include "xparameters.h"
#include "encoder.h"
#include "xstatus.h"
#include "xtmrctr_l.h"

#define PWM_PERIOD            0
#define PWM_DUTY              1
#define PWM_MAX_DUTY_VALUE    0xFFFF


#define less(x,y)  (x < y)              // function comparison elements

#define swap(x,y)  {int t=x; x=y; y=t;} // function swap elements

struct PwmGenerator
{
  u32 APhasePwmBaseAddress;
  u32 BPhasePwmBaseAddress;
  u32 CPhasePwmBaseAddress;
};

void SetPwmGenerator(struct PwmGenerator *pwmGen, u16 power, u16 angle);

void InitPwmGenerator(struct PwmGenerator *pwmGen, struct Encoder *encoder,
    u32 *tmrArray);

/*
* Return sorted timer base address arrey
* where element[0] = A phase timer, element[1] = B phase timer
* element[2] = C phase timer
*/
u32* SortPwm(struct Encoder *encoder, u32 *tmrArray, u32 *sortedTmrArray);

void StartPwmGenerator(struct PwmGenerator *pwmGen);

void StopPwmGenerator(struct PwmGenerator *pwmGen);

void InitPwm(u32 TmrCtrBaseAddress);

/*
 * Start the timer counter
 */
void StartPwm(u32 TmrCtrBaseAddress);

/*
 * Stop the timer counter
 */
void StopPwm(u32 TmrCtrBaseAddress);

/*
 * Set Load register timer 1 counter (duty cycle)
 */
void SetPwmDS(u32 TmrCtrBaseAddress, u16 dutyCycle );


#endif
