#include "common.h"
#include "shared/game_work.h"

#include "common.h"

extern void func_8004D1EC(void *a0, void *a1, u16 a2, void *a3);
/* Set position and rotation targets, adjusting rotation components across the 12-bit wrap. */
void func_8004D294(void *target_position, void *target_rotation, s32 transition_param)
{
  GameView *state = &gameWork.view;
  u16 angle_bits;
  s16 target_angle;
  s16 current_angle;
  s32 angle_delta;
  s32 within_half_turn;
  if (target_position != 0)
  {
    func_8004D1EC(&state->slot[0].unk_04, target_position, transition_param, &state->unk_0A4);
  }
  if (target_rotation != 0)
  {
      register s32 current_angle_wide_m ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    angle_bits = *((u16 *) (((u8 *) target_rotation) + 0));
    if (angle_bits & 0x800)
    {
      target_angle = angle_bits | 0xF800;
    }
    else
    {
      target_angle = angle_bits & 0x7FF;
    }
    *((s16 *) (((u8 *) target_rotation) + 0)) = target_angle;
    angle_bits = *((u16 *) (&state->unk_0AC));
    if (angle_bits & 0x800)
    {
      current_angle = angle_bits | 0xF800;
    }
    else
    {
      current_angle = angle_bits & 0x7FF;
    }
    state->unk_0AC = current_angle;
    {
      current_angle_wide_m = current_angle;
      angle_delta = (*((s16 *) (((u8 *) target_rotation) + 0))) - current_angle_wide_m;
    }
    if (angle_delta < 0)
    {
      angle_delta = -angle_delta;
    }
    within_half_turn = (angle_delta < 0x801);
    angle_bits = *((volatile u16 *) (((u8 *) target_rotation) + 0));
    if (!within_half_turn)
    {
      *((s16 *) (((u8 *) target_rotation) + 0)) = (current_angle & 0xF000) | (angle_bits & 0xFFF);
    }
    angle_bits = *((u16 *) (((u8 *) target_rotation) + 2));
    if (angle_bits & 0x800)
    {
      target_angle = angle_bits | 0xF800;
    }
    else
    {
      target_angle = angle_bits & 0x7FF;
    }
    *((s16 *) (((u8 *) target_rotation) + 2)) = target_angle;
    angle_bits = *((u16 *) (&state->unk_0AE));
    if (angle_bits & 0x800)
    {
      current_angle = angle_bits | 0xF800;
    }
    else
    {
      current_angle = angle_bits & 0x7FF;
    }
    state->unk_0AE = current_angle;
    {
      current_angle_wide_m = current_angle;
      angle_delta = (*((s16 *) (((u8 *) target_rotation) + 2))) - current_angle_wide_m;
    }
    if (angle_delta < 0)
    {
      angle_delta = -angle_delta;
    }
    within_half_turn = (angle_delta < 0x801);
    angle_bits = *((volatile u16 *) (((u8 *) target_rotation) + 2));
    if (!within_half_turn)
    {
      *((s16 *) (((u8 *) target_rotation) + 2)) = (current_angle & 0xF000) | (angle_bits & 0xFFF);
    }
    angle_bits = *((u16 *) (((u8 *) target_rotation) + 4));
    if (angle_bits & 0x800)
    {
      target_angle = angle_bits | 0xF800;
    }
    else
    {
      target_angle = angle_bits & 0x7FF;
    }
    *((s16 *) (((u8 *) target_rotation) + 4)) = target_angle;
    angle_bits = *((u16 *) (&state->viewAngle));
    if (angle_bits & 0x800)
    {
      current_angle = angle_bits | 0xF800;
    }
    else
    {
      current_angle = angle_bits & 0x7FF;
    }
    state->viewAngle = current_angle;
    {
      current_angle_wide_m = current_angle;
      angle_delta = (*((s16 *) (((u8 *) target_rotation) + 4))) - current_angle_wide_m;
    }
    if (angle_delta < 0)
    {
      angle_delta = -angle_delta;
    }
    within_half_turn = (angle_delta < 0x801);
    angle_bits = *((volatile u16 *) (((u8 *) target_rotation) + 4));
    if (!within_half_turn)
    {
      *((s16 *) (((u8 *) target_rotation) + 4)) = (current_angle & 0xF000) | (angle_bits & 0xFFF);
    }
    func_8004D1EC(&state->slot[2].unk_04, target_rotation, transition_param, &state->unk_0AC);
  }
}
