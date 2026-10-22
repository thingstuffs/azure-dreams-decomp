#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_81275000_0_pre {
    u16 unk_00;
} S_81275000_0_pre;   /* the 0x2 bytes before root in func_8014C898, addressed as root[-1] */

typedef struct S_81275000_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
    s16 unk_B0;
    s16 unk_B2;
    s16 unk_B4;
    s16 unk_B6;
} S_81275000_0;   /* root in func_8014C898 */

typedef struct S_81275000_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_81275000_1;   /* owner in func_8014C898 */

typedef struct S_81275000_2 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_81275000_2;   /* part in func_8014C898 */

   /* out in func_8014C898 */

typedef struct S_81275000_5 {
    u8 pad_00[0x1];
    u8 unk_01;
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81275000_5;   /* copy in func_8014C898 */

typedef struct S_81275000_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_81275000_6;   /* callee_part in func_8014C898 */

extern s32 resolve_record_orientation_or_fallback(s32, void *, s16 *, s16);
extern void advance_sprite_animation_and_textures(void *);
extern void play_sound_if_enabled(s32);

void func_8014C898(void *root_data, void *position_data, void *render_data)
;
/* Updates part position, brightness, and flags from the owner and motion state. */
void func_8014C898(void *root_data, void *position_data, void *render_data)
{
    s16 motion_offset[3];
    register MovingPosition *out_pos = position_data;
    SpriteFrameState *render_part= render_data;
    S_81275000_2 *source_pos;
    S_81275000_1 *owner;
    S_81275000_5 *transform;
    S_81275000_6 *motion_part;
    s8 phase;

    owner = ((S_81275000_0 *)root_data)->unk_AC;
    source_pos = owner->unk_0C;
    transform = owner->unk_08;

    if (!(source_pos->unk_14 & 0x80)) {
        render_part->flags &= 0xFF7F;
    }

    out_pos->unk_02 = transform->unk_02;
    out_pos->unk_06 = transform->unk_06;
    out_pos->unk_0A = transform->unk_0A;

    motion_part = owner->unk_0C;
    if (resolve_record_orientation_or_fallback(motion_part->unk_08, motion_part, motion_offset,
                      ((S_81275000_0 *)root_data)->unk_B6) != 0) {
        out_pos->unk_02 +=
            (motion_offset[0] + ((S_81275000_0 *)root_data)->unk_B0) / 2;
        out_pos->unk_06 +=
            (motion_offset[1] + ((S_81275000_0 *)root_data)->unk_B2) / 2;
        out_pos->unk_0A +=
            (motion_offset[2] + ((S_81275000_0 *)root_data)->unk_B4) / 2;
        ((S_81275000_0 *)root_data)->unk_B0 = motion_offset[0];
        ((S_81275000_0 *)root_data)->unk_B2 = motion_offset[1];
        ((S_81275000_0 *)root_data)->unk_B4 = motion_offset[2];
    }

    transform = render_part->source;
    render_part->scale_x = source_pos->unk_1C;
    render_part->scale_y = source_pos->unk_1E;
    render_part->flags = source_pos->unk_14;
    transform->unk_01 &= 0xFE;

    if (((S_81275000_0 *)root_data)->unk_B6 == 1) {
        phase = source_pos->unk_04.s8;
        {
            s32 intensity;

            if (phase < 8) {
                intensity = (phase * 14) + 0x20;
            } else {
                intensity = ((15 - phase) * 14) + 0x20;
            }
            render_part->color.c.b = intensity;
            render_part->color.c.g = intensity;
            render_part->color.c.r = intensity;
        }
        if (!(source_pos->unk_14 & 0x8000) &&
            source_pos->unk_04.u16 == 0x10C) {
            play_sound_if_enabled(0x709);
        }
    }

    if (((S_81275000_0 *)root_data)->unk_B6 == 2) {
        phase = source_pos->unk_04.s8;
        {
            s32 intensity;

            if (phase < 8) {
                intensity = ((7 - phase) * 14) + 0x20;
            } else {
                intensity = ((phase - 8) * 14) + 0x20;
            }
            render_part->color.c.b = intensity;
            render_part->color.c.g = intensity;
            render_part->color.c.r = intensity;
        }
        if (!(source_pos->unk_14 & 0x8000) &&
            source_pos->unk_04.u16 == 0x104) {
            play_sound_if_enabled(0x709);
        }
    }

    advance_sprite_animation_and_textures(render_part);
    if (owner->unk_1E & 0x8000) {
        ((S_81275000_0_pre *)root_data)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

