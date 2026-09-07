#include "common.h"

typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
s32 func_80033B2C();
s32 func_800A9960();
extern s32 func_800A9960_default(void) asm("func_800A9960");
extern s32 func_800A9960_case0(void) asm("func_800A9960");
extern s32 func_800A9960_case2(void) asm("func_800A9960");
s32 func_800A98F8(s32 arg0)
{
  if (arg0 == 2)
  {
    goto case_2;
  }
  if (arg0 < 3)
  {
    if (arg0 == 0)
    {
      goto case_0;
    }
    {
      register s32 zero_result ASM_REG("$2");
      zero_result = 0;
      return zero_result;
      func_800A9960_default();
    }
  }
  if (arg0 == 3)
  {
    goto case_3;
  }
  func_800A9960_default();
  return 0;
  case_0:
  func_80033B2C(0x11FA);

  return func_800A9960_case0();
  case_2:
  func_80033B2C(0x11FB);

  return func_800A9960_case2();
  case_3:
  return func_80033B2C(0x4FA) == 0;

}
