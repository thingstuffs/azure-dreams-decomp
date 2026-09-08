#include "common.h"

extern u16 D_80083164;

void func_800A0150(u8 *src, s8 *dst)
{
  register u8 *p ASM_REG("$8") = src;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
  s16 n;
  s32 a;
  s32 b;
  s32 c;
  n = D_80083164;
  n &= 0x1F;
  if (n & 0x10)
  {
    do
    {
      n = (-n) & 0x1F;
    }
    while (0);
    if (n == 0)
    {
      n = 0x10;
    }
  }
  a = (0x80 - p[0]) * n;
  if (a < 0)
  {
    a += 15;
  }
  a = ((u32) a) >> 4;
  b = (0x80 - p[1]) * n;
  if (b < 0)
  {
    b += 15;
  }
  b = ((u32) b) >> 4;
  c = (0x80 - p[2]) * n;
  if (c < 0)
  {
    c += 15;
  }
  c = ((u32) c) >> 4;
  dst[0] = (-0x80) - a;
  dst[1] = (-0x80) - b;
  n = c;
  dst[2] = (-0x80) - n;
}
