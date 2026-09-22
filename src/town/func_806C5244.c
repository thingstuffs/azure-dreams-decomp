#include "common.h"
#include "m2c_compat.h"
extern M2C_UNK D_80016000;
void func_806C5244(void)
{
  unsigned char new_var;
  (*((M2C_UNK (**)(M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (&D_80016000)) + 0)))) + 0x20)))) + 0x214)))(0);
  new_var = 0x6000;
  (*((M2C_UNK (**)(M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (&D_80016000)) + new_var)))) + 0x20)))) + 0x20C)))(0);
  (*((M2C_UNK (**)(M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (&D_80016000)) + new_var)))) + 0x20)))) + 0x228)))(0);
 ;
}
