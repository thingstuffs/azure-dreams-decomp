#include "common.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
#include "slus.h"
#include "sdk/libgte.h"
#include "dungeon/monster/saber.h"
#include "shared/object_node.h"
#include "dungeon/effect/depth_projection_work.h"
extern u8 resident_globals_page[];

   /* arg1 in spawn_random_velocity_offset_effect */

   /* the 0x2 bytes before arg0 in spawn_random_velocity_offset_effect, addressed as arg0[-1] */


   /* other in spawn_random_velocity_offset_effect */

extern s32 object_flag_block __attribute__((section(".data")));
extern s16 view_facing_angle_alias __attribute__((section(".data")));
extern s8 view_direction_depth_biases[8];

/* Updates the relative position value with an angle bias and flags countdown completion. */
/* Adjusts a Saber effect's draw depth relative to its stored origin and facing, advances animation, and
 * expires its timer. */
void spawn_random_velocity_offset_effect(SelectedItemActionEffectBody *state, MovingPosition *position, Rec_D_80082E80 *result)
{
    DepthProjectionWork work;
    s16 ticks_left;
    s32 position_value;
    s32 reference_value;
    s8 *angle_bias;
    u32 angle_page;
    MovingPosition *reference_pos;

    work.position.vx = position->x;
    work.position.vy = position->y;
    work.position.vz = position->z;
    position_value = RotTransPers(&work.position, &work.screen_xy, &work.depth_cue, &work.gte_flag);

    reference_pos = state->reference_position;
    work.position.vx = reference_pos->x;
    work.position.vy = reference_pos->y;
    work.position.vz = reference_pos->z;
    reference_value = RotTransPers(&work.position, &work.screen_xy, &work.depth_cue, &work.gte_flag);
    angle_page = (u32)resident_globals_page;
    angle_bias = &view_direction_depth_biases[
        ((*(s16 *)(angle_page + 0x3228) +
          state->facing.s + 0x100) >> 9) & 7];
    result->unk_06.as_s16 = position_value - reference_value - *angle_bias * 2;

    advance_sprite_animation_and_textures(result);
    ticks_left = state->ticks_remaining - 1;
    state->ticks_remaining = ticks_left;
    if ((ticks_left << 16) <= 0) {

        angle_page = 0x80080000;
        NODE_HEADER(state)->flags |= 0x8000;
        *(s32 *)(angle_page + 0x14A0) |= 0x8000;
    }
}

/* MECHANISM: DepthProjectionWork fixes the 0x40 frame and the s2/s1/s0 stack-output roles. A retained 0x80080000
   page base yields the displaced angle/global accesses. The table pointer stays in a1. */
