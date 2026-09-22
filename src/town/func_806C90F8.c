#include "common.h"
#include "m2c_compat.h"
M2C_UNK func_80016A78();
M2C_UNK func_80016B20();
s32 func_8001762C(s32, M2C_UNK);
void func_806C90F8(s32 arg0, M2C_UNK arg1)
{
  if (func_8001762C(arg0, arg1) != 0)
  {
    func_80016A78();
  }
  func_80016B20(arg0, arg1);
}

/* MECHANISM: Preserve the 0x20 frame and the s0/s1 argument holds across all three calls.
   Calling func_80016A78 with no source arguments reuses a0 from the branch delay slot,
   leaving its jal delay slot nop; the following reload supplies func_80016B20. */
