#include "shared/actor_status_flags.h"
#include "common.h"
#include "engine/graphics/select_sprite_entry_api.h"
#include "dungeon/actor.h"
#include "dungeon/monster/glacier.h"
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
#include "dungeon/item.h"
#include "sdk/libgte.h"



extern u8 D_801760BC;
extern u8 D_801760C4;

/* Updates the actor's hop animation and finishes the timed movement at its destination tile. */
void update_item_hop_animation(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    u16 direction_aux;
    s32 state;
    s32 move_frames;
    s32 target_x;
    s32 position_component;
    s32 height;
    s32 height_offset;
    s32 frame_count;
    s32 action_timer;
    s32 actor_flags;
    DungeonGlobalStatus *global_base;

    state = action->action_phase;
    switch (state) {
    case 0:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        sprite->frameTable = &D_801760BC;
        select_sprite_entry(
            sprite,
            *(&D_801760BC +
              (((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)),
            0);
        action->action_state_flags |= 8;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        action->unk_9E = 5;
        action->unk_A4.value = 0;
        action->action_phase++;
                        /* fallthrough */
    case 1:
        action->unk_90.value -= action->unk_A4.value;
        sprite->scale_x = 0xC00;
        sprite->scale_y = 0x1400;
        move_frames = action->unk_9E;
        if (move_frames != 0) {
            target_x = sprite->tile_x;
            position_component = motion->x.w.i;
            target_x <<= 6;
            position_component -= 0x20;
            motion->velocity_x = ((target_x - position_component) << 16) / move_frames;

            position_component = motion->y.w.i - 0x20;
            motion->velocity_y =
                (((sprite->tile_y << 6) - position_component) << 16) /
                action->unk_9E;
            action->unk_A4.value =
                (-rsin(action->unk_9E * 0x199)) << 9;
        }

        height = action->unk_90.value;
        height_offset = action->unk_A4.value;
        frame_count = (u16)action->unk_9E;
        height += height_offset;
        frame_count -= 1;
        action->unk_9E = frame_count;
        action->unk_90.value = height;
        if ((frame_count << 16) < 0) {
            action->unk_90.value = 0;
            action->action_state_flags &= 0xFFF7;
            actor->flags1C |= ACTOR_GROUNDED;
            action->action_phase++;
        }
                        /* fallthrough */
    case 2:
        if (actor->flags1C & ACTOR_GROUNDED) {
            action->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            sprite->scale_x = 0x1400;
            sprite->scale_y = 0xC00;
            sprite->frameTable = &D_801760C4;
            select_sprite_entry(
                sprite,
                *(&D_801760C4 +
                  (((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)),
                0);
            action->action_phase++;
        }
        break;
    case 3:
        sprite->scale_x = 0x1000;
        sprite->scale_y = 0x1000;
        break;
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
    sprite->scale_x = 0x1000;
    sprite->scale_y = 0x1000;
    spend_actor_mp(actor, 4);
    advance_status_timers(actor);

    global_base = &g_dungeon_status;
    if (global_base->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&global_base->activity_counts.parts.pending_movement_count)--;
    }

    actor_flags = actor->flags1C;
    if (actor_flags & 0x2000) {
        if (actor->action_flags & ACTOR_ACTION_PENDING) {
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            actor->facing = get_rounded_facing_and_rounding_flag(
                sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        action->unk_8C.address = update_actor_timed_effects;
        on_actor_status_updated(actor);
    }
}
