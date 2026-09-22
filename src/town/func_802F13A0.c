#include "common.h"
#include "m2c_compat.h"
extern void *D_804081AC;
M2C_UNK func_80400948();
s32 func_80404C84();
s32 func_804076C8();
void func_802F13A0(void *arg0)
{
  s32 temp_s1;
  temp_s1 = arg0 - 0x20;
  *((s32 *) (((s8 *) arg0) + 0x20)) = func_80404C84(temp_s1, arg0 + 0xC);
  *((s32 *) (((s8 *) arg0) + 0x24)) = func_804076C8(temp_s1);
  func_80400948();
  *((void **) (((s8 *) arg0) + (-0x10))) = &D_804081AC;
}
/* MECHANISM: Preserved the seed's 0x20 frame, s0/s1 holds, and call/delay-slot shape.
   Replaced the float-rounded address literal with the declared global's address,
   producing retail's %hi/%lo lui+addiu pair and closing both substitutions. */
