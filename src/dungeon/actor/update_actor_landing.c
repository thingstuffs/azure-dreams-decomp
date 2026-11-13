#include "dungeon/actor/movement_path_g00371.h"
#include "shared/actor_status_flags.h"
#include "slus.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor.h"
#include "dungeon/actor/status.h"
#include "dungeon/item.h"
#include "dungeon/player/object.h"

#include "dungeon/actor/spend_actor_mp_api.h"

/* Update airborne movement toward a map tile and finish the landing transition. */
void update_actor_landing(ActorRecord *motion_state, ObjectPosition *transform, SpriteFrameState *map_entity, ActorRecord *actor) {
    u16 direction_aux[2];
    void **animation_table;
    s32 frames_left;
    s16 next_timer;
    s32 target_x;
    s32 velocity_x;
    s32 target_y;
    s32 actor_flags;
    s32 current_x;
    s32 current_y;
    s32 phase;

    phase = motion_state->action_phase;
    switch (phase) {
    case 0:
        motion_state->action_state_flags = (u16) (motion_state->action_state_flags | 8);
        transform->velocity_z = 0xFFF00000;
        actor->flags1C = (s32) (actor->flags1C & ACTOR_GROUNDED_CLEAR_MASK);
        motion_state->unk_A4.value = 0;
        motion_state->action_phase = (u8) (motion_state->action_phase + 1);
    case 1:
        frames_left = motion_state->action_timer;
        motion_state->unk_90.value = (s32) (motion_state->unk_90.value
            - motion_state->unk_A4.value);
        if (frames_left != 0) {
            target_x = map_entity->tile_x << 6;
            current_x = transform->x.w.i - 0x20;
            velocity_x = (s32) ((target_x - current_x) << 0x10) / frames_left;
            current_y = transform->y.w.i - 0x20;
            transform->velocity_x = velocity_x;
            target_y = map_entity->tile_y << 6;
            transform->velocity_y = (s32) ((s32) ((target_y - current_y)
                << 0x10) / motion_state->action_timer);
            motion_state->unk_A4.value = (s32) (motion_state->unk_A4.value
                + transform->velocity_z);
            transform->velocity_z = (s32) (transform->velocity_z + 0x48000);
        }
        motion_state->unk_90.value = (s32) (motion_state->unk_90.value
            + motion_state->unk_A4.value);
        if (motion_state->action_timer < 2) {
            motion_state->unk_90.value = 0;
            motion_state->action_state_flags = (u16) (motion_state->action_state_flags & 0xFFF7);
            actor->flags1C = (s32) (actor->flags1C | ACTOR_GROUNDED);
            motion_state->action_phase = (u8) (motion_state->action_phase + 1);
        }
    case 2:
        if (actor->flags1C & ACTOR_GROUNDED) {
            motion_state->action_state_flags = (u16) (motion_state->action_state_flags & 0xFFF7);
            transform->velocity_z = 0;
            transform->velocity_y = 0;
            transform->velocity_x = 0;
            set_record_integer_tile_center(transform, map_entity->tile_x, map_entity->tile_y);
            animation_table = actor_action_frames;
            map_entity->frameTable = animation_table;
            select_record_entry_and_value(map_entity, *(void **)((u8 *)animation_table + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                + actor->facing + 0x100) >> 7) & 0x1C)), 0);
            motion_state->action_phase = (u8) (motion_state->action_phase + 1);
        }
    default:
        next_timer = motion_state->action_timer - 1;
        motion_state->action_timer = next_timer;
        if ((next_timer << 0x10) <= 0) {
            transform->velocity_z = 0;
            transform->velocity_y = 0;
            transform->velocity_x = 0;
            set_record_integer_tile_center(transform, map_entity->tile_x, map_entity->tile_y);
            spend_actor_mp(actor, 4);
            advance_status_timers(actor);
            if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
                g_dungeon_status.activity_counts.parts.pending_movement_count = (s16) ((u16) g_dungeon_status.activity_counts.parts.pending_movement_count - 1);
            }
            actor_flags = actor->flags1C;
            if (!(actor_flags & ACTOR_PLAYER_SIDE)) {
                if (!(actor_flags & (ACTOR_BLIND | ACTOR_CONFUSED))) {
                    if (actor_flags & ACTOR_PLAYER_AWARE) {
                        actor->facing = get_rounded_facing_and_rounding_flag(map_entity->tile_x,
                            map_entity->tile_y, reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux[0]);
                    }
                }
            }
            if ((check_actor_floor_trap(map_entity, actor) << 0x10) > 0) {
                motion_state->unk_8C.address = &update_actor_facing_animation;
                on_actor_status_updated(actor);
            }
        }
    }
}

