#include "common.h"
#include "m2c_compat.h"
extern volatile unsigned int D_80016000[0x10];
extern M2C_UNK D_8001C048;
void func_80016588(void)
{
  M2C_UNK (*new_var3)(M2C_UNK *, M2C_UNK);
  void **new_var;
  s8 *new_var2;
  new_var2 = ((s8 *) (*D_80016000)) + 0x20;
  new_var = new_var2;
  new_var3 = *((M2C_UNK (**)(M2C_UNK *, M2C_UNK)) (((s8 *) (*new_var)) + 0x268));
  new_var3(&D_8001C048, 1);
}
