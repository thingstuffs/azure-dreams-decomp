#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
#include "slus.h"

   /* arg1 in update_relative_depth_and_expire */

typedef struct S_8102F0D4_1_pre {
    u16 unk_00;
} S_8102F0D4_1_pre;   /* the 0x2 bytes before arg0 in update_relative_depth_and_expire, addressed as arg0[-1] */

typedef struct S_8102F0D4_1 {
    u8 pad_00[0x94];
    s16 unk_94;
    u16 ticks_left; /* 0x96 */
    u8 pad_98[0x10];
    MovingPosition * reference_position; /* 0xA8 */
} S_8102F0D4_1;   /* arg0 in update_relative_depth_and_expire */

extern s8 view_direction_depth_biases[];
s32 RotTransPers(void *vertex, s32 *screen, s32 *p, s32 *flag);

/* Updates relative depth with a direction offset and flags expiration when the countdown ends. */
void update_relative_depth_and_expire(void *state_arg, MovingPosition *position, SpriteFrameState *entity) {
    S_8102F0D4_1 *state = state_arg;
    u16 coords[4];
    s32 transform_result[2];
    s32 transform_aux;
    s32 transform_flags;
    s32 position_depth;
    s32 reference_depth;
    s8 *direction_offset;
    u16 ticks_left;
    MovingPosition *reference_pos;

    coords[0] = position->x;
    coords[1] = position->y;
    coords[2] = position->z;
    position_depth = RotTransPers(coords, transform_result, &transform_aux, &transform_flags);
    reference_pos = state->reference_position;
    coords[0] = reference_pos->x;
    coords[1] = reference_pos->y;
    coords[2] = reference_pos->z;
    reference_depth = RotTransPers(coords, transform_result, &transform_aux, &transform_flags);
    direction_offset = &view_direction_depth_biases[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + state->unk_94 + 0x100)
        >> 9) & 7];
    entity->depth_bias = (s16) ((position_depth - reference_depth) - (*direction_offset * 2));
    advance_sprite_animation_and_textures(entity);
    ticks_left = state->ticks_left - 1;
    state->ticks_left = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_8102F0D4_1_pre *)state)[-1].unk_00 = (u16) (((S_8102F0D4_1_pre *)state)[-1].unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
