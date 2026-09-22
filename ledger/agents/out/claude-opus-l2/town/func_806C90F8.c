#include "common.h"
#include "m2c_compat.h"
M2C_UNK func_80016A78();
M2C_UNK func_80016B20();
s32 func_8001762C(s32, M2C_UNK);
/* Run the optional pre-step when the guard passes, then the main step. */
void func_806C90F8(s32 target, M2C_UNK param)
{
  if (func_8001762C(target, param) != 0)
  {
    func_80016A78();
  }
  func_80016B20(target, param);
}

/* MECHANISM: Preserve the 0x20 frame and the s0/s1 argument holds across all three calls.
   Calling func_80016A78 with no source arguments reuses a0 from the branch delay slot,
   leaving its jal delay slot nop; the following reload supplies func_80016B20. */
