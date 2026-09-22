#include "common.h"
#include "m2c_compat.h"
void func_800A32C8(void *arg0)
{
  M2C_UNK (*new_var2)();
  M2C_UNK (*new_var4)();
  s8 *new_var;
  M2C_UNK (*new_var3)();
  new_var = (s8 *) arg0;
  new_var4 = *((M2C_UNK (**)()) new_var);
  new_var = new_var + 0x68;
  new_var2 = (new_var3 = new_var4);
  new_var2();
}
