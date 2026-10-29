#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
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

typedef struct S_801730E0_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { u16 s; s16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} S_801730E0_0;   /* arg0 in func_801730E0 */


extern s32 rsin(s32);

extern void on_actor_status_updated(void *);



extern s32 weadog_action_resume_address;
extern u8 weadog_frame_set_3[];
extern u8 weadog_frame_set_7[];
extern u8 D_80174ED8[];

/* Moves the actor to its tile with a hop and completes the timed action. */
void advance_weadog_hop(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    u16 facing_aux;
    s32 phase;
    s32 move_ticks;
    s32 actor_flags;
    s32 target_x;
    s32 position_x;
    s32 position_y;
    s16 phase_timer;
    u16 action_timer;
    u8 *anim_table;

    phase = action->action_phase.u;
    switch (phase) {
    case 0:
        phase_timer = action->unk_9E.u - 1;
        action->unk_9E.u = phase_timer;
        if ((phase_timer << 16) != 0) {
            break;
        }

        sprite->frameTable = weadog_frame_set_7;
        select_sprite_entry(
            sprite,
            weadog_frame_set_7[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->action_state_flags |= 8;
        (*(u32 *)&actor->flags1C) &= ACTOR_GROUNDED_CLEAR_MASK;
        action->unk_9E.s = 5;
        action->unk_A0.value = 0;
        action->action_phase.u++;

    case 1:
        move_ticks = action->unk_9E.s;
        action->unk_90.value -= action->unk_A0.value;
        if (move_ticks != 0) {
            target_x = sprite->tile_x;
            position_x = motion->x.w.i;
            target_x <<= 6;
            position_x -= 0x20;
            motion->velocity_x = ((target_x - position_x) << 16) / move_ticks;

            position_y = motion->y.w.i;
            position_y -= 0x20;
            motion->velocity_y =
                (((sprite->tile_y << 6) - position_y) << 16) /
                action->unk_9E.s;
            action->unk_A0.value =
                (-rsin(action->unk_9E.s * 0x199)) << 10;
        }

        action->unk_90.value += action->unk_A0.value;
        phase_timer = action->unk_9E.u - 1;
        action->unk_9E.u = phase_timer;
        if (phase_timer < 0) {
            action->unk_90.value = 0;
            action->action_state_flags &= 0xFFF7;
            (*(u32 *)&actor->flags1C) |= ACTOR_GROUNDED;
            action->action_phase.u++;
        }

    case 2:
        if (((u32)actor->flags1C) & ACTOR_GROUNDED) {
            action->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

            sprite->frameTable = D_80174ED8;
            select_sprite_entry(
                sprite,
                D_80174ED8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            action->action_phase.u++;
        }
        break;

    case 3:
        anim_table = weadog_frame_set_3;
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

    action_timer = action->action_timer.u - 1;
    action->action_timer.u = action_timer;
    if ((s16)action_timer > 0) {
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
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &facing_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        action->unk_8C.address = &weadog_action_resume_address;
        on_actor_status_updated(actor);
    }
}
