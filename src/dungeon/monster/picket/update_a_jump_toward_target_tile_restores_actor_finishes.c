#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/monster/picket.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "engine/graphics.h"

typedef struct S_80172540_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
} S_80172540_0;   /* arg0 in update_a_jump_toward_target_tile_restores_actor_finishes */

s16 get_rounded_facing_and_rounding_flag();
void set_record_integer_tile_center();
s32 advance_status_timers();
extern void on_actor_status_updated(void *actor);
void spend_actor_mp();


extern u8 picket_action_resume_address;
extern u8 D_80174F20[];
extern u8 picket_frame_set_5[];

/* Updates a jump toward the target tile and restores the actor when it finishes. */
void update_a_jump_toward_target_tile_restores_actor_finishes(void *jump_state, ObjectPosition *motion, SpriteFrameState *map_entity, ActorRecord *actor) {
    s32 distance;
    s32 frames_left;
    s16 next_timer;
    s32 actor_flags;
    s32 state;

    state = ((S_80172540_0 *)jump_state)->unk_9B;
    switch (state) {
    case 0:
        if (!(map_entity->flags & 0x6000)) {
            break;
        }
        map_entity->frameTable = D_80174F20;
        select_sprite_entry(
            map_entity,
            D_80174F20[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((S_80172540_0 *)jump_state)->unk_98 |= 8;
        motion->velocity_z = 0xFFEE0000;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        ((S_80172540_0 *)jump_state)->unk_A0 = 0;
        ((S_80172540_0 *)jump_state)->unk_9B++;
    case 1:
        frames_left = ((S_80172540_0 *)jump_state)->unk_96.s;
        ((S_80172540_0 *)jump_state)->unk_90 -= ((S_80172540_0 *)jump_state)->unk_A0;
        if (frames_left != 0) {
            {
                s32 target_x = map_entity->tile_x << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->velocity_x = ((target_x - current_x) << 16) / frames_left;
            }
            {
                s32 target_y = map_entity->tile_y << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->velocity_y = ((target_y - current_y) << 16) /
                    ((S_80172540_0 *)jump_state)->unk_96.s;
            }
            ((S_80172540_0 *)jump_state)->unk_A0 += motion->velocity_z;
            motion->velocity_z += 0x40000;
        }
        ((S_80172540_0 *)jump_state)->unk_90 += ((S_80172540_0 *)jump_state)->unk_A0;
        if (((S_80172540_0 *)jump_state)->unk_96.s < 2) {
            ((S_80172540_0 *)jump_state)->unk_90 = 0;
            ((S_80172540_0 *)jump_state)->unk_98 &= 0xFFF7;
            actor->flags1C |= ACTOR_GROUNDED;
            ((S_80172540_0 *)jump_state)->unk_9B++;
        }
    case 2:
        if (((u32)actor->flags1C) & ACTOR_GROUNDED) {
            ((S_80172540_0 *)jump_state)->unk_98 &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, map_entity->tile_x, map_entity->tile_y);
            map_entity->frameTable = picket_frame_set_5;
            select_sprite_entry(
                map_entity,
                picket_frame_set_5[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((S_80172540_0 *)jump_state)->unk_9B++;
        }
    }

    next_timer = ((S_80172540_0 *)jump_state)->unk_96.u - 1;
    ((S_80172540_0 *)jump_state)->unk_96.s = next_timer;
    if ((next_timer << 16) <= 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, map_entity->tile_x, map_entity->tile_y);
        spend_actor_mp(actor, 3);
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
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
            }
        }

        if ((check_actor_floor_trap(map_entity, actor) << 16) > 0) {
            ((S_80172540_0 *)jump_state)->unk_8C = &picket_action_resume_address;
            on_actor_status_updated(actor);
        }
    }
}
