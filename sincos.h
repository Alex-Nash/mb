#ifndef __SINCOS_H
#define __SINCOS_H

#include <math.h>
#include "xparameters.h"
#include "xbram.h"

#define COS_ARRAY_BASE_ADDRESS		XPAR_BRAM_0_BASEADDR



#define COS_0               0xFFFF
#define COS_90              0x7FFF

#define MAX_ANGLE_VALUE 0x200     // 2*Pi, 360deg ... only 2^
#define ANGLE_120       0xAA      // 2Pi/3
#define ANGLE_240       0x154     // 4Pi/3
#define ANGLE_90        MAX_ANGLE_VALUE >> 2




static XBram CosArray;

u16 GetOrtogonalAngleRight(u16 angle);

u16 GetOrtogonalAngleLeft(u16 angle);

u16 GetReferenceAngle(u16 angle);

u16 Sin (u16 AngleValue);

u16 APhaseCos(u16 angle);

u16 BPhaseCos(u16 angle);

u16 CPhaseCos(u16 angle);

u16 Cos(u16 angle);

void SetCosArray (void);


#endif
