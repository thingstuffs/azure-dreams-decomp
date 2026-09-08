#include "common.h"

typedef struct S_80051548_Ptr
{
  u8 unk00[6];
  u16 cnt;
  u8 unk08[4];
  s32 unk0C;
} S_80051548_Ptr;
typedef struct S_80051548_Obj
{
  S_80051548_Ptr *ptr0;
  s16 state;
  u16 field6;
  u8 unk08[4];
  s16 field0C;
} S_80051548_Obj;
typedef struct S_80051548_VolState
{
  S_80051548_Ptr *ptr0;
  volatile u16 state;
  u16 field6;
  u8 unk08[4];
  s16 field0C;
} S_80051548_VolState;
typedef struct S_80051548_Vec
{
  s32 x;
  s32 y;
  s32 z;
} S_80051548_Vec;
typedef struct S_80051548_Flags
{
  u8 unk[0xC];
  u8 c;
  u8 d;
  u8 e;
} S_80051548_Flags;
extern void func_800478B8(void *arg0);
extern s32 rsin(s32 arg0);
extern s32 rcos(s32 arg0);
extern s32 D_800814A0_abs __attribute__((section(".data")));
__asm__(".set D_800814A0_abs, 0x800814A0");
/* Advances staged object motion and marks completion. */
void func_80051548(S_80051548_Obj *obj, S_80051548_Vec *position, S_80051548_Flags *flags)
{
  s16 state;
  u16 prior_state;
  obj->field6 = obj->field6 + 1;
  func_800478B8(flags);
  state = obj->state;
  switch (state)
  {
  case 1:
    goto move_arc;
  case 0:
  case 2:
    goto wait_trigger;
  case 3:
    goto move_linear;
  default:
    flags->e = 0;
    goto clear_flags;
  }
  move_arc:
  position->x = 0x01C00000 - (((rsin(((s16) obj->field6) << 4) >> 4) * 3) << 14);

  position->y = ((rcos(((s16) obj->field6) << 4) >> 4) << 13) + 0x900000;
  if (((s16) obj->field6) < 0x40)
  {
    return;
  }
  position->x = 0x01000000;
  position->y = 0x900000;
  position->z = 0x700000;
  prior_state = ((S_80051548_VolState *) obj)->state;
  obj->field6 = 0;
  goto advance_state;
  wait_trigger:
  if (obj->field0C == 0)
  {
    return;
  }

  prior_state = ((S_80051548_VolState *) obj)->state;
  obj->field0C = 0;
  obj->field6 = 0;
  advance_state:
  obj->state = prior_state + 1;

  return;
  move_linear:
  position->x = position->x + 0xFFF40000;

  position->y = position->y + 0x20000;
  if (((s16) obj->field6) < 0x40)
  {
    return;
  }
  goto finalize;
  clear_flags:
  flags->d = 0;
  flags->c = 0;

  finalize:
  obj->ptr0->unk0C = 0;

  obj->ptr0->cnt = obj->ptr0->cnt + 1;
  ((u16 *) obj)[-1] |= 0x8000;
  D_800814A0_abs |= 0x8000;
}
