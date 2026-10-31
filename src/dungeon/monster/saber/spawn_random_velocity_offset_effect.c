#include "common.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
#include "slus.h"
#include "sdk/libgte.h"
extern u8 resident_globals_page[];

   /* arg1 in spawn_random_velocity_offset_effect */

typedef struct S_80AC5820_1_pre {
    u16 unk_00;
} S_80AC5820_1_pre;   /* the 0x2 bytes before arg0 in spawn_random_velocity_offset_effect, addressed as arg0[-1] */

typedef struct S_80AC5820_1 {
    u8 pad_00[0x94];
    s16 unk_94;
    u16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
} S_80AC5820_1;   /* arg0 in spawn_random_velocity_offset_effect */

   /* other in spawn_random_velocity_offset_effect */

extern s32 object_flag_block __attribute__((section(".data")));
extern s16 view_facing_angle_alias __attribute__((section(".data")));
extern s8 view_direction_depth_biases[8];

typedef struct StackWork {
    u16 xyz[3];
    u16 pad;
    s64 out18;
    s32 out20;
    s32 out24;
} StackWork;

/* Updates the relative position value with an angle bias and flags countdown completion. */
/* Adjusts a Saber effect's draw depth relative to its stored origin and facing, advances animation, and
 * expires its timer. */
void spawn_random_velocity_offset_effect(void *state_arg, MovingPosition *position, Rec_D_80082E80 *result)
{
    S_80AC5820_1 *state = state_arg;
    StackWork work;
    s16 ticks_left;
    s32 position_value;
    s32 reference_value;
    s8 *angle_bias;
    u32 angle_page;
    MovingPosition *reference_pos;

    work.xyz[0] = position->x;
    work.xyz[1] = position->y;
    work.xyz[2] = position->z;
    position_value = RotTransPers(work.xyz, &work.out18, &work.out20, &work.out24);

    reference_pos = state->unk_A8;
    work.xyz[0] = reference_pos->x;
    work.xyz[1] = reference_pos->y;
    work.xyz[2] = reference_pos->z;
    reference_value = RotTransPers(work.xyz, &work.out18, &work.out20, &work.out24);
    angle_page = (u32)resident_globals_page;
    angle_bias = &view_direction_depth_biases[
        ((*(s16 *)(angle_page + 0x3228) +
          state->unk_94 + 0x100) >> 9) & 7];
    result->unk_06.as_s16 = position_value - reference_value - *angle_bias * 2;

    advance_sprite_animation_and_textures(result);
    ticks_left = state->unk_96 - 1;
    state->unk_96 = ticks_left;
    if ((ticks_left << 16) <= 0) {

        angle_page = 0x80080000;
        ((S_80AC5820_1_pre *)state)[-1].unk_00 |= 0x8000;
        *(s32 *)(angle_page + 0x14A0) |= 0x8000;
    }
}

/* MECHANISM: StackWork fixes the 0x40 frame and the s2/s1/s0 stack-output roles. A retained 0x80080000
   page base yields the displaced angle/global accesses. The table pointer stays in a1. */
