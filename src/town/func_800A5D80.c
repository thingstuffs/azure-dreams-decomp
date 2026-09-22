#include "common.h"
#include "m2c_compat.h"
void func_800A34E0(void *arg0)
{
  s8 *new_var3;
  s8 *new_var4;
  s8 *new_var2;
  M2C_UNK (**new_var5)();
  M2C_UNK (*new_var)();
  new_var4 = (s8 *) arg0;
  new_var2 = 0x68 + new_var2;
  if (1)
  {
    new_var2 = new_var4;
  }
  new_var3 = new_var2;
  new_var5 = (M2C_UNK (**)()) new_var3;
  new_var = *new_var5;
  new_var();
}
