#include "common.h"

extern void func_8004E264(void *a0, s32 a1);
extern u8 *func_8004E280(u8 *a0, s32 *a1);
extern void func_8004E188(void *a0, u8 a1);

void *func_8004E298(u8 *a0, u8 *a1, s32 a2)
{
  u8 *s0;
  u8 *s3;
  u8 *s6;
  u8 *s2;
  s32 s1;
  s32 s5;
  s32 s4;
  s32 sp10;
  s32 v0;
  s32 v1;
  s3 = a0;
  s0 = a1;
  s1 = 0;
  s5 = 0;
  s6 = s3;
  do
  {
    s4 = 0;
  }
  while (0);
  v0 = *s0;
  if (v0 != 0)
  {
    s2 = a0 + 0xA;
    v1 = v0 & 0xFF;
    do
    {
      if (v1 == 0x20)
      {
        s0 += 1;
        {
          s32 t8 = s1 + 8;
          s1 = t8 + s4;
        }
      }
      else if (v1 == 0xA)
      {
        s0 += 1;
        s1 = 0;
        s5 = s5 + 8;
      }
      else if (v1 == 0x9)
      {
        s0 += 1;
        if ((*s0) == 0x73)
        {
          s0 += 1;
          s4 = (*s0) - 0x30;
        }
        else
        {
          s1 += ((*s0) - 0x30) * (s4 + 8);
        }
        s0 += 1;
      }
      else if (v1 == 0x8)
      {
        s0 = func_8004E280(s0 + 1, &a2);
      }
      else if (v1 == 0xC)
      {
        u8 *r;
        r = func_8004E280(s0 + 1, &sp10);
        s1 += sp10;
        s0 = r;
      }
      else
      {
        s8 sep;
        s32 tmp;
        *s3 = 0;
        sep = 0x2C;
        if (a2 & 0x80)
        {
          sep = 0x2E;
        }
        s2[-8] = (u8) (s1 - 0x80);
        s2[-9] = (u8) sep;
        s2[-7] = (u8) (s5 - 0x80);
        *((s16 *) (s2 - 6)) = (s16) (((a2 & 0x300) >> 3) | 0xF);
        func_8004E264(s3, a2);
        func_8004E188(s3, *s0);
        s0 += 1;
        tmp = s2[0];
        s2 += 0xC;
        s3 += 0xC;
        s1 += tmp + s4;
      }
      v0 = *s0;
      v1 = v0 & 0xFF;
    }
    while (v0 != 0);
  }
  if (s3 != s6)
  {
    s3[-0xC] = s3[-0xC] | 0x80;
  }
  else
  {
    s6 = 0;
  }
  return s6;
}
