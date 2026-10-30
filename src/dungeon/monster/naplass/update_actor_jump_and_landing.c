#include "shared/actor_status_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/status.h"
#include "dungeon/item.h"

typedef struct S_80047784 S_80047784;

typedef struct S_80172288_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
} S_80172288_0;   /* arg0 in update_actor_jump_and_landing */

struct SpriteFrameState;
void select_sprite_entry(void *, s16, s16);
void spend_actor_mp(ActorRecord *entity, s32 base_reduction);


extern u8 naplass_action_continuation_address;
extern u8 naplass_frame_set_2[];
extern u8 naplass_frame_set_3[];

/* Updates an actor's jump toward its target tile and completes the landing. */
void update_actor_jump_and_landing(ActorRecord *jump, ObjectPosition *motion, SpriteFrameState *map_entity, ActorRecord *actor) {
    u16 facing_aux;
    s32 jump_ticks;
    s16 ticks_left;
    s32 actor_flags;

    switch (jump->action_phase.u) {
    case 0:
        if (!(map_entity->flags & 0x6000)) {
            break;
        }
        (map_entity->frameTable) = naplass_frame_set_2;
        select_sprite_entry(
            map_entity,
            naplass_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        jump->action_state_flags |= 8;
        motion->velocity_z = 0xFFEE0000;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        jump->unk_A4.value = 0;
        jump->action_phase.u++;

    case 1:
        jump_ticks = jump->action_timer.s;
        jump->unk_90.value -= jump->unk_A4.value;
        if (jump_ticks != 0) {
            {
                s32 target_x = map_entity->tile_x << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->velocity_x = ((target_x - current_x) << 16) / jump_ticks;
            }
            {
                s32 target_y = map_entity->tile_y << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->velocity_y = ((target_y - current_y) << 16) /
                    jump->action_timer.s;
            }
            jump->unk_A4.value += motion->velocity_z;
            motion->velocity_z += 0x40000;
        }
        jump->unk_90.value += jump->unk_A4.value;
        if (jump->action_timer.s < 2) {
            jump->unk_90.value = 0;
            jump->action_state_flags &= 0xFFF7;
            actor->flags1C |= ACTOR_GROUNDED;
            jump->action_phase.u++;
        }

    case 2:
        if (((u32)actor->flags1C) & ACTOR_GROUNDED) {
            jump->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, map_entity->tile_x, map_entity->tile_y);
            (map_entity->frameTable) = naplass_frame_set_3;
            select_sprite_entry(
                map_entity,
                naplass_frame_set_3[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            jump->action_phase.u++;
        }

    default:
        break;
    }

    ticks_left = jump->action_timer.u - 1;
    jump->action_timer.s = ticks_left;
    if ((ticks_left << 16) <= 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, map_entity->tile_x, map_entity->tile_y);
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);
        {

            if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
                g_dungeon_status.activity_counts.parts.pending_movement_count--;
            }
        }

        actor_flags = ((u32)actor->flags1C);
        if (actor_flags & 0x2000) {
            if (actor->action_flags & ACTOR_ACTION_PENDING) {
                actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {

                actor->facing = get_rounded_facing_and_rounding_flag(
                    map_entity->tile_x, map_entity->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &facing_aux);
            }
        }

        if ((check_actor_floor_trap(map_entity, actor) << 16) > 0) {
            jump->unk_8C.address = &naplass_action_continuation_address;
            on_actor_status_updated(actor);
        }
    }
}
