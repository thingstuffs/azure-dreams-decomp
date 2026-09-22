#include "common.h"
#include "m2c_compat.h"
extern int D_80016000[0x10];
void func_800176F0(void)
{
  s8 *new_var;
  new_var = (s8 *) (*D_80016000);
  (*((M2C_UNK (**)(M2C_UNK, M2C_UNK)) (((s8 *) (*((void **) (new_var + 0x20)))) + 0x238)))(0x11, 0x200);
}
