#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/monster/barong.h"
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

typedef struct S_80E7B34C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
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
} S_80E7B34C_0;   /* arg0 in func_80E7B34C */


extern s32 rsin(s32);

extern u8 D_801596F4[];
extern u8 D_8015D554[];
extern u8 D_8015D574[];
extern u8 D_8015D57C[];

/* Updates hop movement and animation, then finalizes the action when its timer expires. */
void hop_actor_and_restore_scale(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 state;
    s32 move_ticks;
    s32 target_x;
    s32 pos_x;
    s32 height_offset;
    s32 height_delta;
    s32 pos_y;
    s32 next_move_ticks;
    s32 action_ticks;
    s32 actor_flags;
    u16 facing_aux;
    DungeonGlobalStatus *global_state;
    u8 *idle_anims;

    state = action->action_phase.u;
    switch (state) {
    case 0:
    {
        u8 *phase_anims;

        if (!(sprite->flags & 0x6000)) {
            break;
        }
        phase_anims = D_8015D574;
        sprite->frameTable = phase_anims;
        select_sprite_entry(sprite,
            phase_anims[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        sprite->scale_y = 0x1000;
        action->action_state_flags |= 8;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        action->unk_9E.s = 5;
        action->unk_A4.value = 0;
        action->action_phase.u++;
    }
    case 1:
        move_ticks = action->unk_9E.s;
        action->unk_90.value -= action->unk_A4.value;
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
                action->unk_9E.s;

            action->unk_A4.value =
                (-rsin(action->unk_9E.s * 0x199)) << 10;
        }

        height_offset = action->unk_90.value;
        height_delta = action->unk_A4.value;
        next_move_ticks = action->unk_9E.u;
        height_offset += height_delta;
        next_move_ticks -= 1;
        action->unk_9E.u = next_move_ticks;
        action->unk_90.value = height_offset;
        if ((next_move_ticks << 16) < 0) {
            action->unk_90.value = 0;
            action->action_state_flags &= 0xFFF7;
            actor->flags1C |= ACTOR_GROUNDED;
            action->action_phase.u++;
        }
    case 2:
    {
        u8 *phase_anims;

        if (actor->flags1C & ACTOR_GROUNDED) {
            action->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            phase_anims = D_8015D57C;
            sprite->frameTable = phase_anims;
            select_sprite_entry(sprite,
                phase_anims[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            sprite->scale_y = 0xC00;
            action->action_phase.u++;
        }
        break;
    }
    case 3:
        idle_anims = D_8015D554;
        if (*(u8 * *)&sprite->frameTable != idle_anims) {
            sprite->frameTable = idle_anims;
            select_sprite_entry(sprite,
                idle_anims[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            sprite->scale_y = 0x1000;
        }
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
    sprite->scale_y = 0x1000;
    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
    spend_actor_mp(actor, 3);
    advance_status_timers(actor);

    global_state = &g_dungeon_status;
    if (global_state->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&global_state->activity_counts.parts.pending_movement_count)--;
    }

    actor_flags = actor->flags1C;
    if (actor_flags & 0x2000) {
        if (actor->action_flags & ACTOR_ACTION_PENDING) {
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    } else {
        if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                actor->facing = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x,
                    sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x,
                    reference_tile_object.tile_position.parts.tile_y,
                    &facing_aux);
            }
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        action->unk_8C.address = D_801596F4;
        on_actor_status_updated(actor);
    }
}
