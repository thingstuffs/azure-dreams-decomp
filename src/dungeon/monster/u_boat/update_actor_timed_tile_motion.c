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


extern s32 rsin(s32);

void create_owner_linked_directional_object(ActorRecord *owner_data, ObjectPosition *source_position, SpriteFrameState *source_sprite);

extern u8 uboat_default_frames[];
extern u8 uboat_timed_motion_frames[];
extern u8 uboat_timed_motion_frames_alt[];
#include "dungeon/monster/u_boat.h"
#include "dungeon/item.h"

/* Updates timed actor movement, landing animations, and the next action. */
void update_actor_timed_tile_motion(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    u16 target_distance;
    s32 phase;

    phase = action->action_phase.u;
    switch (phase) {
    case 0:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        {
            u8 *anim_table = uboat_timed_motion_frames;

            sprite->frameTable = anim_table;
            select_sprite_entry(sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                1);
        }
        action->action_state_flags |= 8;
        actor->flags1C &= 0xF7FFFFFF;
        action->unk_A8.s = 5;
        action->unk_A4.value = 0;
        action->action_phase.u++;
                        /* fallthrough */
    case 1:
    {
        s32 move_ticks;
        s16 next_move_ticks;

        move_ticks = action->unk_A8.s;
        action->unk_90.value -= action->unk_A4.value;
        if (move_ticks != 0) {
            s32 tile_delta;
            s32 axis_pos;

            tile_delta = sprite->tile_x << 6;
            axis_pos = motion->x.w.i;
            axis_pos -= 0x20;
            tile_delta -= axis_pos;
            motion->velocity_x = (tile_delta << 16) / move_ticks;

            axis_pos = motion->y.w.i;
            tile_delta = sprite->tile_y << 6;
            axis_pos -= 0x20;
            tile_delta -= axis_pos;
            motion->velocity_y =
                (tile_delta << 16) / action->unk_A8.s;
            action->unk_A4.value =
                -rsin(action->unk_A8.s * 0x199) << 9;
        }

        action->unk_90.value += action->unk_A4.value;
        next_move_ticks = (u16)action->unk_A8.s - 1;
        action->unk_A8.s = next_move_ticks;
        if (next_move_ticks < 0) {
            action->unk_90.parts.high.s = -0x10;
            action->action_state_flags &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            action->action_phase.u++;
        }
    }
                        /* fallthrough */
    case 2:
        if (actor->flags1C & 0x08000000) {
            action->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            {
                u8 *anim_table = uboat_timed_motion_frames_alt;

                sprite->frameTable = anim_table;
                select_sprite_entry(sprite,
                    anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
            action->action_phase.u++;
        }
        break;
    case 3:
    {
        u8 *anim_table = uboat_default_frames;

        if (*(u8 * *)&sprite->frameTable != anim_table) {
            sprite->frameTable = anim_table;
            select_sprite_entry(sprite,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            if (action->unk_B0.bytes[0] == 0) {
                create_owner_linked_directional_object(action, motion, sprite);
            }
        }
    }
        break;
    }

    {
        u16 action_ticks;

        action_ticks = action->action_timer.u - 1;
        action->action_timer.u = action_ticks;
        if ((action_ticks << 16) > 0) {
            return;
        }
    }

    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
    spend_actor_mp(actor, 0x10);
    advance_status_timers(actor);
    {

        if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
            g_dungeon_status.activity_counts.parts.pending_movement_count = (u16)g_dungeon_status.activity_counts.parts.pending_movement_count - 1;
        }
    }
    {
        s32 actor_flags = actor->flags1C;

        if (actor_flags & 0x2000) {
            if (actor->action_flags & 0x8000) {
                actor->action_flags &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                actor->facing = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &target_distance);
            }
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) <= 0) {
        return;
    }
    action->unk_8C.address = uboat_behavior_entry;
    on_actor_status_updated(actor);
}
