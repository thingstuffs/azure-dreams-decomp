#include "common.h"

#include "common.h"
typedef struct S_80071A68
{
  s32 field_0x00;
} S_80071A68;
extern S_80071A68 D_80071A68[];
extern u32 D_800814A0;
typedef struct S_80051CC4_Owner
{
  u8 unk00[0x6];
  u16 field_0x06;
  u8 unk08[0xC];
  u32 field_0x14;
} S_80051CC4_Owner;
typedef struct S_80051CC4_Sub
{
  S_80051CC4_Owner *owner;
  s16 field_0x04;
  s16 field_0x06;
  u8 pad08[2];
  s16 field_0x0A;
  s16 field_0x0C;
} S_80051CC4_Sub;
typedef struct S_80051CC4_Ptr
{
  u8 pad0[8];
  s32 field_0x08;
  u8 field_0x0C;
  u8 field_0x0D;
  u8 field_0x0E;
} S_80051CC4_Ptr;
/* Fade through seven table entries, then advance the owner and mark completion. */
void func_80051CC4(S_80051CC4_Sub *state, void *unused_arg, S_80051CC4_Ptr *visual)
{
  u8 *flags_page;
  u16 next_tick = state->field_0x06 + 1;
  s32 phase = state->field_0x04;
  u16 saved_phase = *((volatile u16 *) (&state->field_0x04));
  u16 advance_phase;
  u32 flags;
  state->field_0x06 = next_tick;
  switch (phase)
  {
    case 0:
      if (state->field_0x0C != 0)
      {
        advance_phase = state->field_0x04;
        state->field_0x0C = 0;
        goto reset_bump;
      }
      break;

    case 1:
      {
        u8 brightness = visual->field_0x0E + 4;
        visual->field_0x0E = brightness;
        visual->field_0x0D = brightness;
        visual->field_0x0C = brightness;
      }
      if (state->field_0x06 < 0x20)
      {
        break;
      }
      advance_phase = state->field_0x04;
    reset_bump:
      do { state->field_0x06 = 0; } while (0);

      state->field_0x04 = advance_phase + 1;
      break;

    case 2:
      if (((s16) next_tick) >= 0x3F)
      {
        state->field_0x04 = saved_phase + 1;
        state->field_0x06 = 0;
      }
      break;

    case 3:
      {
        u8 brightness = visual->field_0x0E - 4;
        visual->field_0x0E = brightness;
        visual->field_0x0D = brightness;
        visual->field_0x0C = brightness;
      }
      if (state->field_0x06 < 0x20)
      {
        break;
      }
      {
        s16 entry_index = state->field_0x0A + 1;
        state->field_0x0A = entry_index;
        if (entry_index != 7)
        {
          entry_index = entry_index % 7;
          state->field_0x0A = entry_index;
          visual->field_0x08 = (*(&D_80071A68[entry_index])).field_0x00;
          state->field_0x04 = 0;
          state->field_0x06 = 0;
          return;
        }
      }
      goto shared_end;

    default:
      visual->field_0x0E = 0;
      visual->field_0x0D = 0;
      visual->field_0x0C = 0;
    shared_end:
      state->owner->field_0x14 = 0;
      state->owner->field_0x06 = state->owner->field_0x06 + 1;
      *((u16 *) (((u8 *) state) - 2)) |= 0x8000;
      flags = D_800814A0;
      flags |= 0x8000;
      flags_page = (u8 *) 0x80080000;
      *((u32 *) (flags_page + 0x14A0)) = flags;
      break;
  }
}
