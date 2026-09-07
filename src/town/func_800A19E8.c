#include "common.h"

extern s16 func_800374F4(s32 arg0);
extern u8 D_8009EE9C[];
void func_8009F148(void *arg0, void *arg1, void *arg2)
{
  register s32 var_v0 ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
  u8 *s0 = arg0;
  *(((s8 *) arg1) + 0x14) = 1;
  *(((s8 *) arg1) + 0x15) = 1;
  *((s32 *) (((u8 *) arg2) + 0xC)) = 0;
  *((s32 *) (((u8 *) arg2) + 0x10)) = 0;
  *((s32 *) (((u8 *) arg2) + 0x14)) = 0;
  *((s32 *) (s0 + 0xA0)) = 0xFFE00000;
  *((s32 *) (((u8 *) arg2) + 8)) = 0xFFE00000;
  *((u8 **) (s0 + 0x50)) = D_8009EE9C;
  *((s16 *) (s0 + 0x6C)) = func_800374F4(0x1000);
  var_v0 = 0x12;
  if ((*((u8 *) (s0 + 0x4D))) != var_v0)
  {
    var_v0 = 0x59;
  }
  else
  {
    var_v0 = 0x58;
  }
  *((s32 *) (arg0 + 0x60)) = var_v0;
}
