#include "common.h"
#include "m2c_compat.h"
M2C_UNK func_80058588();
s32 func_80071424();
extern s32 D_80084D5C;
void func_80526B18(void *arg0)
{
  s16 temp_v1;
  u16 temp_v0;
  u16 temp_v1_u;
  void *temp_s1;
  temp_s1 = *((void **) (((s8 *) arg0) + 0xC));
  func_80058588(*(*((s16 **) (((s8 *) arg0) + 8))), func_80071424(*((s32 *) (((s8 *) arg0) + 4))), *((s32 *) (((s8 *) arg0) + 4)));
  temp_v1 = *((s16 *) (((s8 *) arg0) + 0));
  if (temp_v1 == 0)
  {
    goto state_0;
  }
  if (temp_v1 == 1)
  {
    goto state_1;
  }
  return;
 do { state_0: temp_v0 = (*((u16 *) (((s8 *) arg0) + 2))) - 1; *((u16 *) (((s8 *) arg0) + 2)) = temp_v0; if ((temp_v0 << 0x10) > 0) { return; } temp_v1_u = (*((u16 *) (((s8 *) arg0) + 0))) + 1; temp_v0 = (*((u16 *) (((s8 *) arg0) + 0x1C))) & 0xFFFD; } while (0);
  *((u16 *) (((s8 *) arg0) + 0x1C)) = temp_v0;
  *((u16 *) (((s8 *) arg0) + 0)) = temp_v1_u;
  return;
  state_1:
  if ((*((u16 *) (((s8 *) temp_s1) + 0x2A))) & 1)
  {
    *((u16 *) (((s8 *) arg0) + (-2))) = (u16) ((*((u16 *) (((s8 *) arg0) + (-2)))) | 0x8000);
    *((s32 *) 0x80084D5C) = D_80084D5C | 0x8000;
  }

}
