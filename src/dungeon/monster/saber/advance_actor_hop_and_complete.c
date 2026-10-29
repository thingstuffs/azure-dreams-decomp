#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/monster/saber.h"
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

typedef struct S_8014EBAC_0 {
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
} S_8014EBAC_0;   /* arg0 in advance_actor_hop_and_complete */


extern s32 rsin(s32);

extern s32 D_8014D728;
extern u8 saber_frame_set_3[];
extern u8 D_80150E0C[];
extern u8 D_80150E14[];

/* Updates the actor's hop toward its tile and completes the timed action. */
void advance_actor_hop_and_complete(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 state;
    s32 hop_ticks;
    s32 target_x;
    s32 pos_x;
    s32 height;
    s32 hop_offset;
    s32 pos_y;
    s32 next_hop_ticks;
    s32 action_ticks;
    s32 actor_flags;
    u16 facing_aux;
    DungeonGlobalStatus *global_base;

    state = action->action_phase.u;
    switch (state) {
    case 0:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        sprite->frameTable = D_80150E0C;
        select_sprite_entry(
            sprite,
            D_80150E0C[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        action->action_state_flags |= 8;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        action->unk_9E.s = 5;
        action->unk_A4 = 0;
        action->action_phase.u++;

    case 1:
        hop_ticks = action->unk_9E.s;
        action->unk_90.value -= action->unk_A4;
        if (hop_ticks != 0) {
            target_x = sprite->tile_x;
            pos_x = motion->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;

            motion->velocity_x = ((target_x - pos_x) << 16) / hop_ticks;

            pos_y = motion->y.w.i;
            pos_y -= 0x20;
            motion->velocity_y =
                (((sprite->tile_y << 6) - pos_y) << 16) /
                action->unk_9E.s;

            action->unk_A4 =
                (-rsin(action->unk_9E.s * 0x199)) << 10;
        }

        height = action->unk_90.value;
        hop_offset = action->unk_A4;
        next_hop_ticks = action->unk_9E.u;
        height += hop_offset;
        next_hop_ticks -= 1;
        action->unk_9E.u = next_hop_ticks;
        action->unk_90.value = height;
        if ((next_hop_ticks << 16) < 0) {
            action->unk_90.value = 0;
            action->action_state_flags &= 0xFFF7;
            actor->flags1C |= ACTOR_GROUNDED;
            action->action_phase.u++;
        }

    case 2:
        if (actor->flags1C & ACTOR_GROUNDED) {
            action->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            sprite->frameTable = D_80150E14;
            select_sprite_entry(
                sprite,
                D_80150E14[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            action->action_phase.u++;
        }
        break;

    case 3:
        if (*(u8 * *)&sprite->frameTable == saber_frame_set_3) {
            break;
        }
        sprite->frameTable = saber_frame_set_3;
        select_sprite_entry(
            sprite,
            saber_frame_set_3[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
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
                sprite->tile_x,
                sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x,
                reference_tile_object.tile_position.parts.tile_y,
                &facing_aux);
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        action->unk_8C.address = &D_8014D728;
        on_actor_status_updated(actor);
    }
}
