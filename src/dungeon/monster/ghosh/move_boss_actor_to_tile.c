#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "sdk/libgte.h"
#include "dungeon/actor.h"
#include "dungeon/item.h"
#include "engine/graphics.h"

typedef struct S_80047784 S_80047784;


struct SpriteFrameState;
#include "dungeon/player/object/set_record_integer_tile_center_api.h"
#include "dungeon/actor/state/advance_status_timers_api.h"
void on_actor_status_updated(void *actor);
struct ActorRecord; struct Rec_D_80082E80; 

typedef struct {
    u8 pad[8];
    s16 count;
} Global83460;

#include "dungeon/monster/ghosh.h"

/* Updates movement toward a tile and completes the timed action. */
void move_boss_actor_to_tile(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *tile, ActorRecord *entity) {
    u16 facing_aux;
    s32 frames_left;
    s32 next_frame;
    s32 x_step;
    s32 status_flags;
    s32 height;
    s32 y_offset;
    s32 entity_flags;
    u16 action_timer;

    switch (action->action_phase.u) {
    case 0:
        action->action_state_flags = (u16) (action->action_state_flags | 8);
        entity->flags1C = (s32) (entity->flags1C & ACTOR_GROUNDED_CLEAR_MASK);
        action->unk_9E.s = 5;
        action->unk_A4 = 0;
        action->action_phase.u = (u8) (action->action_phase.u + 1);
                        /* fall through */
    case 1:
        frames_left = action->unk_9E.s;
        action->unk_90.value = (s32) (action->unk_90.value - action->unk_A4);
        if (frames_left != 0) {
            s32 x_offset;
            x_step = tile->tile_x;

            x_offset = motion->x.w.i;
            x_step <<= 6;
            x_offset -= 0x20;

            x_step = (s32) ((x_step - x_offset) << 0x10) / frames_left;
            y_offset = motion->y.w.i - 0x20;
            motion->velocity_x = x_step;
            motion->velocity_y = (s32) ((s32) (((tile->tile_y << 6) - y_offset) << 0x10) / (s16) action->unk_9E.s);
            action->unk_A4 = (s32) ((0 - rsin(action->unk_9E.s * 0x199)) << 0xA);
        }
        height = action->unk_90.value;
        height += action->unk_A4;
        next_frame = action->unk_9E.u - 1;

        action->unk_9E.s = next_frame;
        action->unk_90.value = height;
        if ((next_frame << 0x10) < 0) {
            action->unk_90.value = 0;
            action->action_state_flags = (u16) (action->action_state_flags & 0xFFF7);
            entity->flags1C = (s32) (entity->flags1C | ACTOR_GROUNDED);
            action->action_phase.u = (u8) (action->action_phase.u + 1);
        }
                        /* fall through */
    case 2:
        if (entity->flags1C & ACTOR_GROUNDED) {
            action->action_state_flags = (u16) (action->action_state_flags & 0xFFF7);
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, tile->tile_x, tile->tile_y);
            action->action_phase.u = action->action_phase.u + 1;
        }
        break;
    case 3:
        if (*(u8 **)&tile->frameTable != ghosh_direction_frames) {
            tile->frameTable = ghosh_direction_frames;
            select_sprite_entry(tile, ghosh_direction_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7], 0);
        }
        break;
    }
    action_timer = action->action_timer.u - 1;
    action->action_timer.u = action_timer;
    if ((action_timer << 0x10) <= 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, tile->tile_x, tile->tile_y);
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
                    entity->facing = get_rounded_facing_and_rounding_flag(tile->tile_x, tile->tile_y, reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &facing_aux);
                }
            }
        }
        if ((check_actor_floor_trap(tile, entity) << 0x10) > 0) {
            action->unk_8C.handler = update_boss_actor_action;
            on_actor_status_updated(entity);
        }
    }
}
