#include "common.h"
#include "m2c_compat.h"
M2C_UNK func_80016104();
extern M2C_UNK D_80018E18;
/* Feed the value to the D_80018E18 record. */
void func_800169D0(s32 value)
{
  M2C_UNK *record;
  record = &D_80018E18;
  func_80016104(record, value);
}
