#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct OffsetPair {
    s16 x;
    s16 y;
} OffsetPair;

typedef struct OffsetTable {
    OffsetPair entries[8];
} OffsetTable;

extern OffsetTable saber_direction_tile_offsets;
#include "dungeon/monster/saber.h"


extern void select_sprite_entry(void *, s32, s32);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern void process_nodes_at_target_tile(void *, s32, s32, s32);
extern void create_randomly_rotated_offset_effect(void *, s32, s32, s32);

typedef struct S_80174A28_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80174A28_0;   /* arg0 in advance_directional_effect_action */


typedef struct S_80174A28_3 {
    u8 pad_00[0x2A];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
} S_80174A28_3;   /* arg3 in advance_directional_effect_action */

/* Advances a timed directional action, triggers its effects, and resets the actor state. */
void advance_directional_effect_action(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    OffsetTable offsets = saber_direction_tile_offsets;
    s32 coord_value;

    switch (action->action_phase) {
    case 0:
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        ((S_80174A28_0 *)action)->unk_96 = 0x14;
        action->action_phase++;
        break;

    case 1:
        if ((--((S_80174A28_0 *)action)->unk_96 == 0x12) ||
            (sprite->flags & 0x8000)) {
            OffsetPair *offset;
            u16 flags;
            s32 height;
            s32 x_sum;
            s32 tile_x;
            s32 x_offset;
            s32 y_offset;
            void *effect_actor;

            flags = sprite->flags;
            effect_actor = actor;
            sprite->flags = flags | 0x0800;
            height = motion->z.w.i;
            tile_x = sprite->tile_x;
            offset = &offsets.entries[(((S_80174A28_3 *)actor)->unk_2A.u >> 9) & 7];
            x_offset = offset->x;
            x_sum = tile_x + x_offset;
            y_offset = offset->y;
            x_sum = x_sum & 0xFFFF;
            coord_value = sprite->tile_y + y_offset;
            create_randomly_rotated_offset_effect(effect_actor, x_sum, coord_value & 0xFFFF, height);
        }
        if ((((S_80174A28_0 *)action)->unk_96 == 0x0A) ||
            (sprite->flags & 0x8000)) {
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x605);
        }
        if ((((S_80174A28_0 *)action)->unk_96 == 9) ||
            (sprite->flags & 0x8000)) {
            OffsetPair *offset;
            u16 angle;
            s32 height;
            s32 tile_x;
            s32 x;
            s32 x_sum;
            s32 y_offset;

            angle = ((S_80174A28_3 *)actor)->unk_2A.u;
            offset = offsets.entries + ((angle >> 9) & 7);
            height = motion->z.w.i;
            tile_x = sprite->tile_x;
            coord_value = offset->x;
            x_sum = tile_x + coord_value;
            y_offset = offset->y;
            coord_value = sprite->tile_y + y_offset;
            x = x_sum & 0xFFFF;
            process_nodes_at_target_tile(actor, x, coord_value & 0xFFFF, height);
        }
        if ((((S_80174A28_0 *)action)->unk_96 <= 0) ||
            (sprite->flags & 0x8000)) {
            ((S_80174A28_0 *)action)->unk_96 = 0;
            action->action_phase++;
        }
        break;

    case 2:
        if (sprite->flags & 0xE000) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion,
                sprite->tile_x, sprite->tile_y);
            if (*(u8 **)&sprite->frameTable != saber_direction_frames) {
                sprite->frameTable = saber_direction_frames;
                sprite->flags &= 0xF7FF;
                select_sprite_entry(sprite,
                    (*(u8 **)&sprite->frameTable)[((g_game_work.view.camera_rotation.parts.viewAngle +
                        ((S_80174A28_3 *)actor)->unk_2A.s + 0x100) >> 9) & 7],
                    0);
                action->action_phase++;
            }
        }
        break;

    case 3:
        spend_actor_mp(actor, 0x400);
        ((S_80174A28_0 *)action)->unk_8C = &saber_behavior_entry;
        g_dungeon_status.active_actor = 0;
        actor->action_flags &= 0x7FFF;
        break;
    }
}
