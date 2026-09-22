#include "common.h"
#include "m2c_compat.h"
extern int D_80016000[0x10];
void func_8001A670(void)
{
  (*((M2C_UNK (**)(M2C_UNK, M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (*D_80016000)) + 0x20)))) + 0x2F4)))(-(1 ^ 0), -5);
}
