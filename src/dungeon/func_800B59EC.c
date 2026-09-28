#include "shared/game_work.h"
#include "shared/object_flags.h"
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef struct 
{
  void *next;
  u8 pad04[0x0D - 4];
  u8 field0D;
  u8 pad0E[0x14 - 0x0E];
  s16 state;
  s16 count;
  u16 flags;
  s16 phase;
} S_800BB14C;
typedef struct 
{
  u8 pad00[0x0C];
  s8 valueC;
  s8 valueD;
  s8 valueE;
  u8 pad0F[0x1E - 0x0F];
  u16 amount;
} S_800BB14C_TARGET;
/* Animates the target amount and selected channels, then marks the effect finished after fading. */
void func_800BB14C(void *effect_data, register S_800BB14C *effect, S_800BB14C_TARGET *target)
{
  s16 state;
  effect = (S_800BB14C *) effect_data;
  state = effect->state;
  if (state == 1)
  {
    goto check_status;
  }
  if (state < 2)
  {
    if (state == 0)
    {
      goto state_zero;
    }
    goto update_values;
  }
  if (state == 2)
  {
    goto state_two;
  }
  goto update_values;
  state_zero:
  {
    s16 phase = effect->phase;
    u16 amount = target->amount + (phase * 0x10);
    target->amount = amount;
    if (amount < 0x4001U)
    {
      target->amount = 0x4000;
      effect->state = ((s16) effect->state) + 1;
    }
  }

  goto check_status;
  check_status:
  if ((((S_800BB14C_TARGET *) effect->next)->amount & 0x8000) == 0)
  {
    goto update_values;
  }

  effect->count = 4;
  effect->state = 2;
  goto update_values;
  state_two:
  {
    s16 fade_ticks = effect->count;
    if (fade_ticks != 0)
    {
      u16 amount = target->amount;
      target->amount = amount - (((s32) amount) / fade_ticks);
    }
  }

  {
    s16 fade_ticks = ((u16) effect->count) - 1;
    effect->count = fade_ticks;
    if (fade_ticks < 0)
    {
      u16 header_flags = ((volatile u16 *) effect)[-1];
      ((u16 *) effect)[-1] = header_flags | 0x8000;
      objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
      goto done;
    }
  }
  goto update_values;
  update_values:
  {
    u16 phase;
    s8 pulse_value;
    u8 pulse_step;
    phase = effect->phase;
    phase += 1;
    pulse_value = (effect->field0D - 4) & 0xBF;
    do
    {
      effect->phase = phase;
    }
    while (0);
    effect->field0D = pulse_value;
    pulse_step = effect->phase;
    pulse_step &= 0x1F;
    if ((phase & 0x20) != 0)
    {
      pulse_value = 0x30 - pulse_step;
    }
    else
    {
      pulse_value = pulse_step + 0x10;
    }
    if (effect->flags & 1)
    {
      target->valueC = pulse_value;
    }
    if (effect->flags & 2)
    {
      target->valueD = pulse_value;
    }
    if (effect->flags & 4)
    {
      target->valueE = pulse_value;
    }
  }

  done:
  return;
}
