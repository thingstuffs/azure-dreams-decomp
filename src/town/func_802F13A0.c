#include "common.h"
#include "m2c_compat.h"
extern void *D_804081AC;
M2C_UNK func_80400948();
s32 func_80404C84();
s32 func_804076C8();
/* Cache the task's two computed fields and arm the D_804081AC handler. */
void func_802F13A0(void *task)
{
  s32 owner;
  owner = task - 0x20;
  *((s32 *) (((s8 *) task) + 0x20)) = func_80404C84(owner, task + 0xC);
  *((s32 *) (((s8 *) task) + 0x24)) = func_804076C8(owner);
  func_80400948();
  *((void **) (((s8 *) task) + (-0x10))) = &D_804081AC;
}
/* MECHANISM: Preserved the seed's 0x20 frame, s0/s1 holds, and call/delay-slot shape.
   Replaced the float-rounded address literal with the declared global's address,
   producing retail's %hi/%lo lui+addiu pair and closing both substitutions. */
