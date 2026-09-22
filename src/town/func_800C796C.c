#include "common.h"
#include "m2c_compat.h"
M2C_UNK func_800C4174(void *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_80082660;
/* Clear the object's slot in the D_80082660 table, then run the shared handler. */
void func_800C50CC(void *obj, M2C_UNK param_a, M2C_UNK param_b)
{
  *(((u8 *) (&D_80082660)) + ((*((s32 *) (((s8 *) obj) + 0x60))) * 8)) = 0;
  func_800C4174(obj, param_a, param_b);
}
