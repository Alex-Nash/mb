
#include "cos_arm.h"

int SetCosArray ()
{
    double delta;
    uint32_t i;
    uint32_t cosValue[COS_ARRAY_LENGTH];

    delta = 2.0 * M_PI / COS_ARRAY_LENGTH;

    for (i=0; i < COS_ARRAY_LENGTH; i++)
    {
        cosValue[i] = (uint32_t)((0xFFFFFFFF)/2 * (cos(i * delta) + 1));
    }

    BramMemoryWrite((uint32_t) MEM_OFFSET_COS, cosValue, COS_ARRAY_LENGTH);

    return 0;
}
