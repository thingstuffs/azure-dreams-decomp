#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

   /* arg1 in apply_relative_projected_depth */

typedef struct S_8102F20C_1_pre {
    u16 unk_00;
} S_8102F20C_1_pre;   /* the 0x2 bytes before arg0 in apply_relative_projected_depth, addressed as arg0[-1] */

typedef struct S_8102F20C_1 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    u8 pad_1E[0xA];
    MovingPosition * reference_position; /* 0x28 */
} S_8102F20C_1;   /* arg0 in apply_relative_projected_depth */



typedef struct S_8102F20C_3 {
    u8 pad_00[0x6];
    s16 depth_bias; /* 0x06 */
    u8 pad_08[0xC];
    u16 unk_14;
} S_8102F20C_3;   /* out in apply_relative_projected_depth */


typedef struct {
    u16 x0;
    u16 x1;
    u16 x2;
} Stack3;

extern s8 view_direction_depth_biases[];
extern s32 RotTransPers(void *, void *, void *, void *);
extern void advance_sprite_animation_and_textures(void *);

/* Apply a relative projected depth with a direction bias and propagate output status flags. */
void apply_relative_projected_depth(void *entity, MovingPosition *position, void *output) {
    Stack3 coords;
    s32 projection_flags;
    s32 depth_cue;
    s32 screen_xy[2];
    s16 depth_delta;
    s32 depth_bias;
    MovingPosition *base_position;
    S_8102F20C_3 *result;

    result = output;
    coords.x0 = position->unk_02;
    coords.x1 = position->unk_06;
    coords.x2 = position->unk_0A;
    depth_delta = RotTransPers(&coords.x0, &screen_xy, &depth_cue, &projection_flags);
    base_position = ((S_8102F20C_1 *)entity)->reference_position;
    coords.x0 = base_position->unk_02;
    coords.x1 = base_position->unk_06;
    coords.x2 = base_position->unk_0A;
    depth_delta = depth_delta - RotTransPers(&coords.x0, &screen_xy, &depth_cue, &projection_flags);
    depth_bias = view_direction_depth_biases[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((S_8102F20C_1 *)entity)->unk_1C + 0x100) >> 9) & 7] * 2;
    depth_delta = depth_delta + depth_bias;
    result->unk_14 = (u16) (result->unk_14 & 0xFF7F);
    result->depth_bias = depth_delta;
    advance_sprite_animation_and_textures(result);
    if (result->unk_14 & 0x6000) {
        ((S_8102F20C_1_pre *)entity)[-1].unk_00 = (u16) (((S_8102F20C_1_pre *)entity)[-1].unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
