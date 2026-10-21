#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172290_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
} S_80172290_0;   /* arg0 in complete_actor_arc_movement */

extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void advance_status_timers(void *);
extern void on_actor_status_updated(void *);
extern void spend_actor_mp(void *, s32);
extern s32 check_actor_floor_trap(void *, void *);

extern s32 D_80170E5C;

/* Advance arcing movement toward the destination tile and finalize the landing. */
void complete_actor_arc_movement(S_80172290_0 *animation, ObjectPosition *motion, Rec_D_80082E80 *destination, ActorRecord *entity) {
    s32 query_output;
    s32 frames_left;
    s32 entity_flags;
    s32 phase;

    phase = animation->unk_9B;
    switch (phase) {
    case 0:
        animation->unk_98 |= 8;
        motion->velocity_z = 0xFFEE0000;
        entity->flags1C &= 0xF7FFFFFF;
        animation->unk_A0 = 0;
        animation->unk_9B++;
    case 1:
        frames_left = animation->unk_96.s;
        animation->unk_90 -= animation->unk_A0;
        if (frames_left != 0) {
            {
                s32 target_x = ((SpriteFrameState *)destination)->unk_24 << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->velocity_x = ((target_x - current_x) << 16) / frames_left;
            }
            {
                s32 target_y = ((SpriteFrameState *)destination)->unk_25 << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->velocity_y =
                    ((target_y - current_y) << 16) / animation->unk_96.s;
            }
            animation->unk_A0 += motion->velocity_z;
            motion->velocity_z += 0x40000;
        }

        animation->unk_90 += animation->unk_A0;
        if (animation->unk_96.s < 2) {
            animation->unk_90 = 0;
            animation->unk_98 &= 0xFFF7;
            entity->flags1C |= 0x08000000;
            animation->unk_9B++;
        }
    case 2:
        if (entity->flags1C & 0x08000000) {
            animation->unk_98 &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)destination)->unk_24, ((SpriteFrameState *)destination)->unk_25);
            animation->unk_9B++;
        }
    }

    if ((s16)--animation->unk_96.u <= 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)destination)->unk_24, ((SpriteFrameState *)destination)->unk_25);
        spend_actor_mp(entity, 4);
        advance_status_timers(entity);

        {
            DungeonGlobalStatus *global_state = &g_dungeon_status;

            if (global_state->activity_counts.parts.pending_movement_count != 0) {
                (*(u16 *)&global_state->activity_counts.parts.pending_movement_count)--;
            }
        }

        entity_flags = entity->flags1C;
        if (entity_flags & 0x2000) {
            if (entity->action_flags & 0x8000) {
                entity->action_flags &= 0x7FFF;
            }
        } else if (!(entity_flags & 0x410)) {
            if (entity_flags & 0x20000) {

                entity->facing = get_rounded_facing_and_rounding_flag(
                    ((SpriteFrameState *)destination)->unk_24, ((SpriteFrameState *)destination)->unk_25,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &query_output);
            }
        }

        if ((check_actor_floor_trap(destination, entity) << 16) > 0) {
            animation->unk_8C = &D_80170E5C;
            on_actor_status_updated(entity);
        }
    }

    return;
}
