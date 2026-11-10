#include "dungeon/monster/weadog_frames.h"
#include "common.h"
#include "dungeon/actor.h"
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

extern s32 D_8015FCE8;
extern u8 D_80162EB8[];
extern u8 D_80162ED0[];

/* Moves an actor to its tile with a timed hop, updates animation, and completes the action. */
void move_actor_to_tile_with_hop(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    u16 direction_aux;
    s32 state;
    s32 move_ticks;
    s32 actor_flags;
    s32 target_x;
    s32 pos_x;
    s32 pos_y;
    s16 phase_ticks;
    u16 action_ticks;
    u8 *anim_table;

    state = action->action_phase;
    switch (state) {
    case 0:
        phase_ticks = action->unk_9E - 1;
        action->unk_9E = phase_ticks;
        if ((phase_ticks << 16) != 0) {
            break;
        }

        sprite->frameTable = D_80162ED0;
        select_sprite_entry(
            sprite,
            D_80162ED0[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->action_state_flags |= 8;
        actor->flags1C &= 0xF7FFFFFF;
        action->unk_9E = 5;
        action->unk_A0.value = 0;
        action->action_phase++;

    case 1:
        move_ticks = action->unk_9E;
        action->unk_90.value -= action->unk_A0.value;
        if (move_ticks != 0) {
            target_x = sprite->tile_x;
            pos_x = motion->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;
            motion->velocity_x = ((target_x - pos_x) << 16) / move_ticks;

            pos_y = motion->y.w.i;
            pos_y -= 0x20;
            motion->velocity_y =
                (((sprite->tile_y << 6) - pos_y) << 16) /
                action->unk_9E;
            action->unk_A0.value =
                (-rsin(action->unk_9E * 0x199)) << 10;
        }

        action->unk_90.value += action->unk_A0.value;
        phase_ticks = action->unk_9E - 1;
        action->unk_9E = phase_ticks;
        if (phase_ticks < 0) {
            action->unk_90.value = 0;
            action->action_state_flags &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            action->action_phase++;
        }

    case 2:
        if (actor->flags1C & 0x08000000) {
            action->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

            sprite->frameTable = weadog_frame_set_6;
            select_sprite_entry(
                sprite,
                weadog_frame_set_6[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            action->action_phase++;
        }
        break;

    case 3:
        anim_table = D_80162EB8;
        if (*(u8 * *)&sprite->frameTable != anim_table) {
            sprite->frameTable = anim_table;
            select_sprite_entry(
                sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }

    default:
        break;
    }

    action_ticks = action->action_timer - 1;
    action->action_timer = action_ticks;
    if ((s16)action_ticks > 0) {
        return;
    }

    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
    spend_actor_mp(actor, 4);
    advance_status_timers(actor);

    if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
        g_dungeon_status.activity_counts.parts.pending_movement_count--;
    }

    actor_flags = actor->flags1C;
    if (actor_flags & 0x2000) {
        if (actor->action_flags & 0x8000) {
            actor->action_flags &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            actor->facing = get_rounded_facing_and_rounding_flag(
                sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        action->unk_8C.word_ptr = &D_8015FCE8;
        on_actor_status_updated(actor);
    }
}
