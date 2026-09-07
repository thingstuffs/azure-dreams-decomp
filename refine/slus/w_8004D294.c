#include "common.h"

#include "common.h"

typedef struct 
{
  char pad0[0xA4];
  s16 f_A4;
  s16 f_A6;
  s16 f_A8;
  s16 f_AA;
  s16 f_AC;
  s16 f_AE;
  s16 f_B0;
  s16 f_B2;
  void *callback;
  void *field_B8;
  char pad_bc[0x140 - 0xBC];
  void *field_140;
  char pad_144[0x1C4 - 0x144];
} S_80083178_local;
extern void func_8004D1EC(void *a0, void *a1, u16 a2, void *a3);
/* Set position and rotation targets, adjusting rotation components across the 12-bit wrap. */
void func_8004D294(void *target_position, void *target_rotation, s32 transition_param)
{
  S_80083178_local *state = (S_80083178_local *)&D_80083178;
  u16 angle_bits;
  s16 target_angle;
  s16 current_angle;
  s32 angle_delta;
  s32 within_half_turn;
  if (target_position != 0)
  {
    func_8004D1EC(&state->field_B8, target_position, transition_param, &state->f_A4);
  }
  if (target_rotation != 0)
  {
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
    angle_bits = *((u16 *) (&state->f_AC));
    if (angle_bits & 0x800)
    {
      current_angle = angle_bits | 0xF800;
    }
    else
    {
      current_angle = angle_bits & 0x7FF;
    }
    state->f_AC = current_angle;
    {
      register s32 current_angle_wide ASM_REG("$3") = current_angle;   /* MATCH pin: slus-diff */
      angle_delta = (*((s16 *) (((u8 *) target_rotation) + 0))) - current_angle_wide;
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
    angle_bits = *((u16 *) (&state->f_AE));
    if (angle_bits & 0x800)
    {
      current_angle = angle_bits | 0xF800;
    }
    else
    {
      current_angle = angle_bits & 0x7FF;
    }
    state->f_AE = current_angle;
    {
      register s32 current_angle_wide ASM_REG("$3") = current_angle;   /* MATCH pin: slus-diff */
      angle_delta = (*((s16 *) (((u8 *) target_rotation) + 2))) - current_angle_wide;
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
    angle_bits = *((u16 *) (&state->f_B0));
    if (angle_bits & 0x800)
    {
      current_angle = angle_bits | 0xF800;
    }
    else
    {
      current_angle = angle_bits & 0x7FF;
    }
    state->f_B0 = current_angle;
    {
      register s32 current_angle_wide ASM_REG("$3") = current_angle;   /* MATCH pin: slus-diff */
      angle_delta = (*((s16 *) (((u8 *) target_rotation) + 4))) - current_angle_wide;
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
    func_8004D1EC(&state->field_140, target_rotation, transition_param, &state->f_AC);
  }
}
