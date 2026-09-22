#include "common.h"
#include "m2c_compat.h"
extern M2C_UNK D_80016000;
void func_80016658(void)
{
  char new_var;
  void *temp_v1;
  void *temp_v1_2;
  (*((M2C_UNK (**)(M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (&D_80016000)) + 0)))) + 0x20)))) + 0x248)))(0);
  new_var = 0x6000;
  temp_v1 = *((void **) (((s8 *) (*((void **) (((s8 *) (&D_80016000)) + new_var)))) + 0x1C));
  *((s32 *) (((s8 *) temp_v1) + 0x10)) = (s32) ((*((s32 *) (((s8 *) temp_v1) + 4))) + 0x28);
  temp_v1_2 = *((void **) (((s8 *) (*((void **) (((s8 *) (&D_80016000)) + new_var)))) + 0x1C));
  *((s32 *) (((s8 *) temp_v1_2) + 0x14)) = (s32) (*((s32 *) (((s8 *) temp_v1_2) + 8)));
}
