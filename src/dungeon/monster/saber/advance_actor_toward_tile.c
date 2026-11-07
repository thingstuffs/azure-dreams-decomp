#include "shared/actor_status_flags.h"
#include "dungeon/monster/saber_frames.h"
#include "dungeon/monster/saber.h"
#include "dungeon/actor.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/item.h"
#include "sdk/libgte.h"

extern s32 D_80159728;
extern u8 D_8015CE0C[];
extern u8 D_8015CE14[];

/* Updates movement toward a tile, its animation phases, and action completion. */
void finish_saber_tile_hop(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity) {
    s32 phase;
    s32 frames_left;
    s32 target_x;
    s32 pos_x;
    s32 height;
    s32 height_offset;
    s32 pos_y;
    s32 next_frame;
    s32 action_timer;
    s32 entity_flags;
    u16 target_distance;
    DungeonGlobalStatus *shared_state;
    phase = action->action_phase;
    switch (phase) {
    case 0:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        sprite->frameTable = D_8015CE0C;
        select_sprite_entry(
            sprite,
            D_8015CE0C[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        action->action_state_flags |= 8;
        entity->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        action->unk_9E = 5;
        action->unk_A4.value = 0;
        action->action_phase++;
    case 1:
        frames_left = (s16)(action->unk_9E);
        action->unk_90.value -= action->unk_A4.value;
        if (frames_left != 0) {
            target_x = sprite->tile_x;
            pos_x = motion->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;
            motion->velocity_x = ((target_x - pos_x) << 16) / frames_left;
            pos_y = motion->y.w.i;
            pos_y -= 0x20;
            motion->velocity_y =
                (((sprite->tile_y << 6) - pos_y) << 16) /
                (s16)(action->unk_9E);
            action->unk_A4.value =
                (-rsin((s16)(action->unk_9E) * 0x199)) << 10;
        }
        height = action->unk_90.value;
        height_offset = action->unk_A4.value;
        next_frame = action->unk_9E;
        height += height_offset;
        next_frame -= 1;
        action->unk_9E = next_frame;
        action->unk_90.value = height;
        if ((next_frame << 16) < 0) {
            action->unk_90.value = 0;
            action->action_state_flags &= 0xFFF7;
            entity->flags1C |= ACTOR_GROUNDED;
            action->action_phase++;
        }
    case 2:
        if (entity->flags1C & ACTOR_GROUNDED) {
            action->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            sprite->frameTable = D_8015CE14;
            select_sprite_entry(
                sprite,
                D_8015CE14[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            action->action_phase++;
        }
        break;
    case 3:
        if (*(u8 * *)&sprite->frameTable == saber_frame_set_5) {
            break;
        }
        sprite->frameTable = saber_frame_set_5;
        select_sprite_entry(
            sprite,
            saber_frame_set_5[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
    }
    action_timer = action->action_timer - 1;
    action->action_timer = action_timer;
    if ((action_timer << 16) > 0) {
        return;
    }
    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
    spend_actor_mp(entity, 4);
    advance_status_timers(entity);
    shared_state = &g_dungeon_status;
    if (shared_state->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&shared_state->activity_counts.parts.pending_movement_count)--;
    }
    entity_flags = entity->flags1C;
    if (entity_flags & 0x2000) {
        if (entity->action_flags & ACTOR_ACTION_PENDING) {
            entity->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    } else if (!(entity_flags & 0x410)) {
        if (entity_flags & 0x20000) {
            entity->facing = get_rounded_facing_and_rounding_flag(
                sprite->tile_x,
                sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x,
                reference_tile_object.tile_position.parts.tile_y,
                &target_distance);
        }
    }
    if ((check_actor_floor_trap(sprite, entity) << 16) > 0) {
        action->unk_8C.address = &D_80159728;
        on_actor_status_updated(entity);
    }
}
