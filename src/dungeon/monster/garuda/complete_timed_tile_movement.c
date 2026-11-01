#include "shared/actor_status_flags.h"
#include "dungeon/monster/garuda.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
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
#include "dungeon/actor.h"



extern s32 rsin(s32);

extern u8 D_801748A0[];
extern u8 D_801748A8[];
extern u8 garuda_frame_set_4[];

/* Advance a timed movement animation, snap the entity to its tile, and finish the action. */
void complete_timed_tile_movement(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *entity)
{
    s32 direction_work[2];
    s32 state;
    s32 move_ticks;
    s32 target_x;
    s32 world_x;
    s32 arc_base;
    s32 arc_offset;
    s32 world_y;
    s32 height_offset;
    s32 next_move_ticks;
    s32 entity_mask;
    s32 action_ticks;
    s32 entity_flags;
    s32 facing_index;
    DungeonGlobalStatus *global_base;

    state = action->action_phase.u;
    switch (state) {
    case 0:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        (sprite->frameTable) = D_801748A0;
        facing_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(sprite, D_801748A0[facing_index & 7], 0);
        action->action_state_flags |= 8;
        entity->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        action->unk_B0.halves.low.s = 5;
        action->unk_A0.value = 0;
        action->action_phase.u++;
        break;
    case 1:
        action->unk_90.value += 0xC0000;
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        (sprite->frameTable) = D_801748A8;
        facing_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(sprite, D_801748A8[facing_index & 7], 0);
        action->action_state_flags |= 8;
        entity->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        action->unk_B0.halves.low.s = 5;
        action->unk_A0.value = 0;
        action->unk_90.value -= 0x400000;
        action->action_phase.u++;
                        /* fall through */
    case 2:
        move_ticks = action->unk_B0.halves.low.s;
        action->unk_90.value -= action->unk_A0.value;
        if (move_ticks != 0) {
            target_x = sprite->tile_x;
            world_x = motion->x.w.i;
            target_x <<= 6;
            world_x -= 0x20;
            motion->velocity_x = ((target_x - world_x) << 16) / move_ticks;

            world_y = motion->y.w.i;
            world_y -= 0x20;
            motion->velocity_y =
                (((sprite->tile_y << 6) - world_y) << 16) /
                action->unk_B0.halves.low.s;

            arc_base = (0 - rsin(action->unk_B0.halves.low.s * 0x199)) << 10;
            action->unk_A0.value = arc_base + (arc_base >> 1);
        }

        height_offset = action->unk_90.value;
        arc_offset = action->unk_A0.value;
        next_move_ticks = action->unk_B0.halves.low.u;
        height_offset += arc_offset;
        next_move_ticks -= 1;
        action->unk_B0.halves.low.u = next_move_ticks;
        action->unk_90.value = height_offset;
        if ((next_move_ticks << 16) < 0) {

            entity_mask = 0x08000000;
            action->unk_90.value = 0;
            action->action_state_flags &= 0xFFF7;
            entity->flags1C |= entity_mask;
            (sprite->frameTable) = garuda_frame_set_4;
            facing_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
            select_sprite_entry(sprite, garuda_frame_set_4[facing_index & 7], 0);
            action->action_phase.u++;
        }
                        /* fall through */
    case 3:
        if (!(entity->flags1C & ACTOR_GROUNDED)) {
            break;
        }
        action->action_state_flags &= 0xFFF7;
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        (sprite->frameTable) = garuda_frame_set_4;
        facing_index = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(sprite, garuda_frame_set_4[facing_index & 7], 0);
        action->action_phase.u++;

        break;
    default:
        break;
    }

    action_ticks = action->action_timer.u - 1;
    action->action_timer.u = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
    spend_actor_mp(entity, 4);
    advance_status_timers(entity);

    global_base = &g_dungeon_status;
    if (global_base->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&global_base->activity_counts.parts.pending_movement_count)--;
    }

    entity_flags = entity->flags1C;
    if (entity_flags & 0x2000) {
        if (entity->action_flags & ACTOR_ACTION_PENDING) {
            entity->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    } else if (!(entity_flags & 0x410)) {
        if (entity_flags & 0x20000) {
            entity->facing = get_rounded_facing_and_rounding_flag(
                sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, direction_work);
        }
    }
    action->unk_8C.address = update_creature_animation_action;
    on_actor_status_updated(entity);
}
