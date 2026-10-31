#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "shared/dungeon_moving_views.h"
#include "engine/scene.h"
#include "dungeon/system.h"
#include "dungeon/monster/beldo.h"

typedef struct S_81263000_0_pre {
    u16 unk_00;
} S_81263000_0_pre;   /* the 0x2 bytes before root in create_flagged_actor_object_2, addressed as root[-1] */


typedef struct S_81263000_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_81263000_1;   /* owner in create_flagged_actor_object_2 */

typedef struct S_81263000_2 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_81263000_2;   /* part in create_flagged_actor_object_2 */

   /* out in create_flagged_actor_object_2 */

typedef struct S_81263000_5 {
    u8 pad_00[0x1];
    u8 unk_01;
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81263000_5;   /* copy in create_flagged_actor_object_2 */

extern void advance_sprite_animation_and_textures(void *);


/* Update part position, shading, and flags from its owner. */
void create_flagged_actor_object_2(AttachedSpriteWithOffsetBody *root, void *output_pos_arg, void *target_data)
{
    MovingPosition *output_pos = output_pos_arg;
    GteShortVector offset;
    S_81263000_2 *position_data;
    SpriteFrameState *target_part= target_data;
    S_81263000_1 *owner;
    S_81263000_5 *pos_data;
    SpriteFrameState *motion_part;
    s8 phase;
    s16 shade_a;
    s32 reverse_phase;

    owner = root->unk_AC.pointer;
    position_data = owner->unk_0C;
    pos_data = owner->unk_08;

    if (!(position_data->unk_14 & 0x80)) {
        target_part->flags &= 0xFF7F;
    }

    output_pos->x = pos_data->unk_02;
    output_pos->y = pos_data->unk_06;
    output_pos->z = pos_data->unk_0A;

    motion_part = owner->unk_0C;
    if (resolve_record_orientation_or_fallback(motion_part->source, motion_part, &offset,
                      root->unk_B6) != 0) {
        output_pos->x +=
            (offset.vx + root->unk_B0.s) / 2;
        output_pos->y +=
            (offset.vy + root->unk_B2.s) / 2;
        output_pos->z +=
            (offset.vz + root->unk_B4.s) / 2;
        root->unk_B0.s = offset.vx;
        root->unk_B2.s = offset.vy;
        root->unk_B4.s = offset.vz;
    }

    pos_data = target_part->source;
    target_part->scale_x = position_data->unk_1C;
    target_part->scale_y = position_data->unk_1E;
    target_part->flags = position_data->unk_14;
    pos_data->unk_01 &= 0xFE;

    if (root->unk_B6 == 1) {
        phase = position_data->unk_04.s8;
        if (phase < 8) {
            shade_a = (phase * 14) + 0x20;
            target_part->color.c.b = shade_a;
            target_part->color.c.g = shade_a;
            target_part->color.c.r = shade_a;
        } else {
            shade_a = ((15 - phase) * 14) + 0x20;
            target_part->color.c.b = shade_a;
            target_part->color.c.g = shade_a;
            target_part->color.c.r = shade_a;
        }
        if (!(position_data->unk_14 & 0x8000) &&
            position_data->unk_04.u16 == 0x10C) {
            play_sound_if_enabled(0x709);
        }
    }

    if (root->unk_B6 == 2) {
        phase = position_data->unk_04.s8;
        if (phase < 8) {
            reverse_phase = 7;
            reverse_phase -= phase;
        } else {
            reverse_phase = phase - 8;
        }
        {
            s32 shade =
                ((reverse_phase * 7) * 2) + 0x20;

            target_part->color.c.b = shade;
            target_part->color.c.g = shade;
            target_part->color.c.r = shade;
        }
        if (!(position_data->unk_14 & 0x8000) &&
            position_data->unk_04.u16 == 0x104) {
            play_sound_if_enabled(0x709);
        }
    }

    advance_sprite_animation_and_textures(target_part);
    if (owner->unk_1E & 0x8000) {
        ((S_81263000_0_pre *)root)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

