#include "common.h"
#include "m2c_compat.h"
M2C_UNK func_800C4174(void *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_80082660;
void func_800C50CC(void *arg0, M2C_UNK arg1, M2C_UNK arg2)
{
  *(((u8 *) (&D_80082660)) + ((*((s32 *) (((s8 *) arg0) + 0x60))) * 8)) = 0;
  func_800C4174(arg0, arg1, arg2);
}
