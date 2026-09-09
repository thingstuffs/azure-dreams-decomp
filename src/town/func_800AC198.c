#include "common.h"
#include "m2c_compat.h"

s32 func_80033B2C();
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
      s32 zero_result;
      zero_result = 0;
      return zero_result;
    }
  }
  if (arg0 == 3)
  {
    goto case_3;
  }
  goto tail;
  case_0:
  return func_80033B2C(0x11FA);
  case_2:
  return func_80033B2C(0x11FB);
  case_3:
  return func_80033B2C(0x4FA) == 0;
  tail:
  return 0;

}
