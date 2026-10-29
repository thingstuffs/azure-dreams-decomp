#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/status.h"


extern s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void on_actor_status_updated(void *actor);
extern void spend_actor_mp(ActorRecord *entity, s32 base_reduction);


extern u8 maximum_action_continuation_address;

/* Advances a jump toward the target tile and finishes movement when the timer expires. */
void advance_jump_to_target_tile(ActorRecord *motion, ObjectPosition *position, SpriteFrameState *target_tile, ActorRecord *entity) {
    u16 direction_aux;
    s32 jump_state;
    s32 frames_left;
    s16 next_frames;
    s32 entity_flags;

    jump_state = motion->action_phase.u;
    switch (jump_state) {
    case 0:
        if (motion->action_timer.s != 8) {
            break;
        }
        motion->action_state_flags |= 8;
        position->velocity_z = 0xFFEE0000;
        entity->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        motion->unk_A4 = 0;
        motion->action_phase.u++;
                        /* fall through */
    case 1:
        frames_left = motion->action_timer.s;
        motion->unk_90.value -= motion->unk_A4;
        if (frames_left != 0) {
            s32 coord;
            s32 axis_origin;
            s32 coord2;
            s32 axis_origin2;

            coord = target_tile->tile_x << 6;
            axis_origin = position->x.w.i - 0x20;
            position->velocity_x = ((coord - axis_origin) << 16) / frames_left;
            coord2 = target_tile->tile_y << 6;
            axis_origin2 = position->y.w.i - 0x20;
            position->velocity_y = ((coord2 - axis_origin2) << 16) / motion->action_timer.s;
            motion->unk_A4 += position->velocity_z;
            position->velocity_z += 0x40000;
        }
        motion->unk_90.value += motion->unk_A4;
        if (motion->action_timer.s < 3) {
            motion->unk_90.value = 0;
            motion->action_state_flags &= 0xFFF7;
            entity->flags1C |= ACTOR_GROUNDED;
            motion->action_phase.u++;
        }
                        /* fall through */
    case 2:
        if (entity->flags1C & ACTOR_GROUNDED) {
            motion->action_state_flags &= 0xFFF7;
            position->velocity_z = 0;
            position->velocity_y = 0;
            position->velocity_x = 0;
            set_record_integer_tile_center(position, target_tile->tile_x, target_tile->tile_y);
            motion->action_phase.u++;
        }
        break;
    }

    next_frames = (u16)motion->action_timer.s - 1;
    motion->action_timer.s = next_frames;
    if ((next_frames << 16) <= 0) {
        position->velocity_z = 0;
        position->velocity_y = 0;
        position->velocity_x = 0;
        set_record_integer_tile_center(position, target_tile->tile_x, target_tile->tile_y);
        spend_actor_mp(entity, 5);
        advance_status_timers(entity);

        if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
            g_dungeon_status.activity_counts.parts.pending_movement_count = (u16)g_dungeon_status.activity_counts.parts.pending_movement_count - 1;
        }

        entity_flags = entity->flags1C;
        if (entity_flags & 0x2000) {
            if (entity->action_flags & ACTOR_ACTION_PENDING) {
                entity->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
            }
        } else if (!(entity_flags & 0x410)) {
            if (entity_flags & 0x20000) {

                entity->facing = get_rounded_facing_and_rounding_flag(
                    target_tile->tile_x, target_tile->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
            }
        }

        if ((check_actor_floor_trap(target_tile, entity) << 16) > 0) {
            motion->unk_8C.address = &maximum_action_continuation_address;
            on_actor_status_updated(entity);
        }
    }
}
