#include "common.h"

extern u16 D_80083164;

/* Blends three source channels toward 0x80 using a triangular phase weight. */
void func_800A0150(u8 *src, s8 *dst)
{
  register u8 *channels ASM_REG("$8") = src;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
  s16 weight;
  s32 delta_0;
  s32 delta_1;
  s32 delta_2;
  weight = D_80083164;
  weight &= 0x1F;
  if (weight & 0x10)
  {
    do
    {
      weight = (-weight) & 0x1F;
    }
    while (0);
    if (weight == 0)
    {
      weight = 0x10;
    }
  }
  delta_0 = (0x80 - channels[0]) * weight;
  if (delta_0 < 0)
  {
    delta_0 += 15;
  }
  delta_0 = ((u32) delta_0) >> 4;
  delta_1 = (0x80 - channels[1]) * weight;
  if (delta_1 < 0)
  {
    delta_1 += 15;
  }
  delta_1 = ((u32) delta_1) >> 4;
  delta_2 = (0x80 - channels[2]) * weight;
  if (delta_2 < 0)
  {
    delta_2 += 15;
  }
  delta_2 = ((u32) delta_2) >> 4;
  dst[0] = (-0x80) - delta_0;
  dst[1] = (-0x80) - delta_1;
  weight = delta_2;
  dst[2] = (-0x80) - weight;
}
