#include "shared/actor_status_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/item.h"

typedef struct S_80174F24_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} S_80174F24_0;   /* arg0 in spawn_randomized_oscillating_effect */

typedef struct S_80174F24_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174F24_3;   /* arg1 in spawn_randomized_oscillating_effect */


extern s32 rsin(s32);

extern s32 pulunpa_variant_action_address;
extern u8 D_80176338[];
extern u8 D_80176340[];

/* Updates the actor's movement animation and finishes the timed action. */
void spawn_randomized_oscillating_effect(ActorRecord *body, void *motion_arg, SpriteFrameState *sprite, ActorRecord *actor)
{
    u16 direction_aux;
    u8 move_state;

    move_state = body->action_phase.u;
    switch (move_state) {
    case 0:
        if (sprite->flags & 0x6000) {
            u8 *direction_table = D_80176338;

            (sprite->frameTable) = direction_table;
            select_sprite_entry(sprite,
                direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            body->action_state_flags |= 8;
            actor->flags1C &= ~ACTOR_GROUNDED;
            body->unk_9E.s = 5;
            body->unk_A0.value = 0;
            body->action_phase.u++;
        } else {
            break;
        }
                        /* fall through */

    case 1:
    {
        s16 move_ticks;
        s32 target_delta;
        s32 axis_pos;
        s32 x_velocity;

        body->unk_90.value -= body->unk_A0.value;
        move_ticks = body->unk_9E.s;
        if (move_ticks != 0) {
            target_delta = sprite->tile_x << 6;
            axis_pos = ((S_80174F24_3 *)motion_arg)->unk_02 - 0x20;
            target_delta -= axis_pos;
            x_velocity = (target_delta << 16) / move_ticks;

            axis_pos = ((S_80174F24_3 *)motion_arg)->unk_06;
            ((S_80174F24_3 *)motion_arg)->unk_0C = x_velocity;
            axis_pos -= 0x20;
            target_delta = sprite->tile_y << 6;
            target_delta -= axis_pos;
            ((S_80174F24_3 *)motion_arg)->unk_10 =
                (target_delta << 16) / body->unk_9E.s;

            body->unk_A0.value =
                (-rsin(body->unk_9E.s * 409)) << 9;
        }

        body->unk_90.value += body->unk_A0.value;
        move_ticks = body->unk_9E.u - 1;
        body->unk_9E.s = move_ticks;
        if (move_ticks < 0) {
            body->unk_90.value = 0;
            body->action_state_flags &= 0xFFF7;
            actor->flags1C |= ACTOR_GROUNDED;
            body->action_phase.u++;
        }
    }
                        /* fall through */

    case 2:
        if (((u32)actor->flags1C) & ACTOR_GROUNDED) {
            u8 *direction_table;

            body->action_state_flags &= 0xFFF7;
            ((S_80174F24_3 *)motion_arg)->unk_14 = 0;
            ((S_80174F24_3 *)motion_arg)->unk_10 = 0;
            ((S_80174F24_3 *)motion_arg)->unk_0C = 0;
            set_record_integer_tile_center(motion_arg,
                sprite->tile_x, sprite->tile_y);
            direction_table = D_80176340;
            (sprite->frameTable) = direction_table;
            select_sprite_entry(sprite,
                direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            body->action_phase.u++;
        }
        break;

    default:
        break;
    }

    {
        s16 action_ticks;
        u32 actor_flags;

        action_ticks = body->action_timer.u - 1;
        body->action_timer.s = action_ticks;
        if (action_ticks > 0) {
            return;
        }

        ((S_80174F24_3 *)motion_arg)->unk_14 = 0;
        ((S_80174F24_3 *)motion_arg)->unk_10 = 0;
        ((S_80174F24_3 *)motion_arg)->unk_0C = 0;
        set_record_integer_tile_center(motion_arg,
            sprite->tile_x, sprite->tile_y);
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);

        if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
            g_dungeon_status.activity_counts.parts.pending_movement_count--;
        }

        actor_flags = ((u32)actor->flags1C);
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
            body->unk_8C.address = &pulunpa_variant_action_address;
            on_actor_status_updated(actor);
        }
    }
}
