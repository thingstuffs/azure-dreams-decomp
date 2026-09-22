#include "common.h"
#include "m2c_compat.h"
extern unsigned int D_80016000[0x10];
void func_8001A634(void)
{
  (*((M2C_UNK (**)(M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (*D_80016000)) + 0x20)))) + 0x30C)))(0x8000);
}
