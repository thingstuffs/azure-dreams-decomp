#include "common.h"
#include "m2c_compat.h"
extern unsigned long long D_80016000[0x10];
void func_8001A5BC(void)
{
  (*((M2C_UNK (**)(M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (*D_80016000)) + 0x20)))) + 0x280)))(0xD1);
}
