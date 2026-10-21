#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80047784 S_80047784;

typedef struct S_801704A0_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    u8 pad_A0[0x4];
    s32 unk_A4;
} S_801704A0_0;   /* arg0 in move_boss_actor_to_tile */

void select_sprite_entry(S_80047784 *object, s16 table_index, s16 entry_index);
s32 func_800644B8();
s16 get_rounded_facing_and_rounding_flag();
#include "dungeon/player/object/set_record_integer_tile_center_api.h"
#include "dungeon/actor/state/advance_status_timers_api.h"
void on_actor_status_updated(void *actor);
struct ActorRecord; struct Rec_D_80082E80; s32 check_actor_floor_trap(struct Rec_D_80082E80 *, struct ActorRecord *);
typedef struct {
    u8 pad[0x24];
    u8 x;
    u8 y;
} Global82E80;
typedef struct {
    u8 pad[8];
    s16 count;
} Global83460;
extern u8 D_8016F78C[];
extern u8 D_80174A2C[];

/* Updates movement toward a tile and completes the timed action. */
void move_boss_actor_to_tile(S_801704A0_0 *action, ObjectPosition *motion, Rec_D_80082E80 *tile, ActorRecord *entity) {
    s32 facing_aux;
    s32 frames_left;
    s32 next_frame;
    s32 x_step;
    s32 status_flags;
    s32 height;
    s32 y_offset;
    s32 entity_flags;
    u16 action_timer;

    switch (action->unk_9B) {
    case 0:
        action->unk_98 = (u16) (action->unk_98 | 8);
        entity->flags1C = (s32) (entity->flags1C & 0xF7FFFFFF);
        action->unk_9E.s = 5;
        action->unk_A4 = 0;
        action->unk_9B = (u8) (action->unk_9B + 1);
                        /* fall through */
    case 1:
        frames_left = action->unk_9E.s;
        action->unk_90 = (s32) (action->unk_90 - action->unk_A4);
        if (frames_left != 0) {
            s32 x_offset;
            x_step = tile->unk_24;

            x_offset = motion->x.w.i;
            x_step <<= 6;
            x_offset -= 0x20;

            x_step = (s32) ((x_step - x_offset) << 0x10) / frames_left;
            y_offset = motion->y.w.i - 0x20;
            motion->velocity_x = x_step;
            motion->velocity_y = (s32) ((s32) (((tile->unk_25 << 6) - y_offset) << 0x10) / (s16) action->unk_9E.s);
            action->unk_A4 = (s32) ((0 - func_800644B8(action->unk_9E.s * 0x199)) << 0xA);
        }
        height = action->unk_90;
        height += action->unk_A4;
        next_frame = action->unk_9E.u - 1;

        action->unk_9E.s = next_frame;
        action->unk_90 = height;
        if ((next_frame << 0x10) < 0) {
            action->unk_90 = 0;
            action->unk_98 = (u16) (action->unk_98 & 0xFFF7);
            entity->flags1C = (s32) (entity->flags1C | 0x08000000);
            action->unk_9B = (u8) (action->unk_9B + 1);
        }
                        /* fall through */
    case 2:
        if (entity->flags1C & 0x08000000) {
            action->unk_98 = (u16) (action->unk_98 & 0xFFF7);
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, tile->unk_24, tile->unk_25);
            action->unk_9B = action->unk_9B + 1;
        }
        break;
    case 3:
        if (tile->unk_2C.as_pu8 != D_80174A2C) {
            tile->unk_2C.as_pu8 = D_80174A2C;
            select_sprite_entry(tile, D_80174A2C[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7], 0);
        }
        break;
    }
    action_timer = action->unk_96 - 1;
    action->unk_96 = action_timer;
    if ((action_timer << 0x10) <= 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, tile->unk_24, tile->unk_25);
        advance_status_timers(entity);
        if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
            g_dungeon_status.activity_counts.parts.pending_movement_count = (u16) g_dungeon_status.activity_counts.parts.pending_movement_count - 1;
        }
        entity_flags = entity->flags1C;
        if (entity_flags & 0x2000) {
            status_flags = entity->action_flags;
            if (status_flags & 0x8000) {
                entity->action_flags = status_flags & 0x7FFF;
            }
        } else {
            if (!(entity_flags & 0x410)) {
                if (entity_flags & 0x20000) {
                    entity->facing = get_rounded_facing_and_rounding_flag(tile->unk_24, tile->unk_25, D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y,
                        &facing_aux);
                }
            }
        }
        if ((check_actor_floor_trap(tile, entity) << 0x10) > 0) {
            action->unk_8C = D_8016F78C;
            on_actor_status_updated(entity);
        }
    }
}
