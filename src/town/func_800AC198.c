#include "common.h"
#include "m2c_compat.h"

s32 func_80033B2C();
/* Returns the selected query result, testing for zero for check type 3. */
s32 func_800A98F8(s32 check_type)
{
  if (check_type == 2)
  {
    goto case_2;
  }
  if (check_type < 3)
  {
    if (check_type == 0)
    {
      goto case_0;
    }
    return 0;
  }
  if (check_type == 3)
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
