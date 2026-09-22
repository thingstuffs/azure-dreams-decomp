#include "common.h"
#include "m2c_compat.h"
void func_800B6754(void *arg0)
{
  s8 *new_var;
  new_var = (s8 *) arg0;
  (*((M2C_UNK (**)()) new_var))();
  new_var = new_var + 0x68;
}
