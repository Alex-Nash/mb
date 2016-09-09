#include "sincos.h"


u16 GetOrtogonalAngleRight(u16 angle)
{
  u16 newAngle;
  newAngle = GetReferenceAngle(angle);
  return GetReferenceAngle((newAngle + ANGLE_90));
}

u16 GetOrtogonalAngleLeft(u16 angle)
{
  u16 newAngle;
  newAngle = GetReferenceAngle(angle);
  if(newAngle >= ANGLE_90)
    return (u16)(newAngle - ANGLE_90);
  return (u16) MAX_ANGLE_VALUE + ANGLE_90 - NewAngle;
}

u16 GetReferenceAngle(u16 angle)
{
  // angle & 0x1FF
  return (angle & (MAX_ANGLE_VALUE - 1));
}

u16 Sin (u16 AngleValue)
{
  return Cos(AngleValue + ANGLE_90);
}

u16 APhaseCos(u16 angle)
{
  return Cos(angle);
}

u16 BPhaseCos(u16 angle)
{
  return Cos(angle + ANGLE_120 );
}

u16 CPhaseCos(u16 angle)
{
  return Cos(angle + ANGLE_240 );
}

u16 Cos(u16 angle)
{
  u16 CosValue, tmpAngleValue;
  tmpAngleValue = GetReferenceAngle(angle);  // return value between 0x000..0x1FF
  // read cos value from cos array
  CosValue = (u32) XBram_ReadReg(COS_ARRAY_BASE_ADDRESS, tmpAngleValue);
  return (u16)(CosValue >> 16);
  }
}

// переделать
void SetCosArray (void)
{
  double Delta;
  u32 i;

  Delta = 2.0 * M_PI / MAX_ANGLE_VALUE;

  for (i=0; i < MAX_ANGLE_VALUE; i++)
  {
    XBram_WriteReg((u32)COS_ARRAY_BASE_ADDRESS, (u32) i,(u32) ((0xFFFFFFFF)/2 * (cos(i * Delta) + 1)));
  }

}
