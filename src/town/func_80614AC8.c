#include "common.h"
#include "m2c_compat.h"
extern M2C_UNK D_80016000;
/* Call the scene object's 0x248 method, then advance the state's x field by 0x20. */
void func_80614AC8(void)
{
  void *state;
  (*((M2C_UNK (**)(M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (&D_80016000)) + 0)))) + 0x20)))) + 0x248)))(0);
  state = *((void **) (((s8 *) (*((void **) (((s8 *) (&D_80016000)) + 0)))) + 0x1C));
  *((s32 *) (((s8 *) state) + 4)) = (s32) ((*((s32 *) (((s8 *) state) + 4))) + 0x20);
}
