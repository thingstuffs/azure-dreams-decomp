#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
/* Call the scene object's 0x214, 0x20C and 0x228 methods with 0. */
void func_806C5244(void)
{
  (*((M2C_UNK (**)(M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (((M2C_UNK *)&D_80016000))) + 0)))) + 0x20)))) + 0x214)))(0);
  (*((M2C_UNK (**)(M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (((M2C_UNK *)&D_80016000))) + 0)))) + 0x20)))) + 0x20C)))(0);
  (*((M2C_UNK (**)(M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (((M2C_UNK *)&D_80016000))) + 0)))) + 0x20)))) + 0x228)))(0);
}
