#include "common.h"
#include "m2c_compat.h"
extern M2C_UNK D_80016000;
/* Call the scene object's 0x248 method, then copy the state's two coordinate pairs across with an offset. */
void func_80016658(void)
{
  void *state;
  void *state_2;
  (*((M2C_UNK (**)(M2C_UNK)) (((s8 *) (*((void **) (((s8 *) (*((void **) (((s8 *) (&D_80016000)) + 0)))) + 0x20)))) + 0x248)))(0);
  state = *((void **) (((s8 *) (*((void **) (((s8 *) (&D_80016000)) + 0)))) + 0x1C));
  *((s32 *) (((s8 *) state) + 0x10)) = (s32) ((*((s32 *) (((s8 *) state) + 4))) + 0x28);
  state_2 = *((void **) (((s8 *) (*((void **) (((s8 *) (&D_80016000)) + 0)))) + 0x1C));
  *((s32 *) (((s8 *) state_2) + 0x14)) = (s32) (*((s32 *) (((s8 *) state_2) + 8)));
}
