#include "town/player/init_movement_action.h"
#include "town/player/initialize_record_and_select_active_data.h"
#include "town/player/object.h"
#include "town/player/action_initializers.h"
#include "script_symbols.h"
#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "shared/entity.h"


#include "engine/object/test_resident_bitmap_bit_api.h"
#include "town/player/coordinates.h"
#include "town/map.h"
#include "town/map/position.h"
#include "town/player/input.h"
#include "town.h"
extern void submit_object_resource_data();
void init_ground_input_fallback(s32 * *, void *, void *);
struct TownObjectRecord; void initialize_randomized_object_action(struct TownObjectRecord *, ObjectPosition *, SpriteFrameState *);
struct TownObjectRecord; void init_input_angle_random_timer_action(struct TownObjectRecord *, ObjectPosition *, SpriteFrameState *);
struct TownObjectRecord;
struct TownObjectRecord; struct ObjectPosition; void initialize_actor_action_state(struct TownObjectRecord *, struct ObjectPosition *, s32);
void initialize_action_object(s32 * *, void *, void *);
struct TownObjectRecord;
struct TownObjectRecord; void initialize_action_object_with_counter(struct TownObjectRecord *, ObjectPosition *, s32);
void initialize_actor_movement_interaction_action(s32 * *, void *, void *);
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"
#include "town/player.h"
#include "town/player/position_handlers.h"

extern s32 town_actor_control[];


typedef struct S_80091260_2 {
    u8 pad_00[0x16];
    s16 unk_16;
    u8 pad_18[0x14];
    s32 unk_2C;
    u8 pad_30[0xE];
    u16 unk_3E;
} S_80091260_2;   /* arg0 in dispatch_actor_input_actions */

/* Dispatch actor actions from input flags and position checks. */
void dispatch_actor_input_actions(S_80091260_2 *actor, ObjectPosition *position, SpriteFrameState *sprite) {
    GameWork *input_state = &g_game_work;
    s32 input_flags;
    s32 action_result;
    s32 tile_id;
    s16 height;
    s16 remaining_count;
    s32 *action_data;

    resolve_collision_axis_order(position);
    step_perpendicular_to_input(position);

    height = query_capped_surface_height(position, &position_query_scratch);
    if ((height - position->z.w.i) >= 4) {
        if (town_action_state_flag == 0) {
            initialize_action_object((s32 * *)(actor), position, sprite);
            return;
        }
    } else if (town_action_state_flag == 0) {
        set_height_and_slope_velocity((position), height, (struct TownVec * *)(&position_query_scratch));
    }

    input_flags = (input_state->pressed_buttons);
    if (input_flags & 0x10) {
        initialize_actor_action_state((struct TownObjectRecord *)(actor), (position), (s32)sprite);
        return;
    }

    if (input_flags & 0x40) {
        action_result = select_adjacent_source_entry(actor, town_actor_control);
        if (action_result != 0) {
            if (action_result == 2) {
                initialize_actor_movement_interaction_action((s32 * *)(actor), position, sprite);
                return;
            } else {
                initialize_action_object_with_counter((struct TownObjectRecord *)(actor), (position), (s32)sprite);
                return;
            }
        } else if (test_resident_bitmap_bit(F_t_attack_enable) != 0) {
            init_threshold_countdown_action((struct TownObjectRecord *)(actor), position, sprite);
            return;
        }
        return;
    }

    action_data = town_actor_control;
    action_result = select_entry_by_input_direction(action_data);
    if (action_result != 0) {
        if (action_result == -1) {
            store_input_angle(actor);
            initialize_record_and_select_active_data(actor, (position), sprite);
            actor->unk_2C = 0;
            submit_object_resource_data(action_data[4]);
            return;
        } else {
            init_movement_action((struct TownObjectRecord *)(actor), position, sprite);
            return;
        }
        return;
    }

    input_flags = input_state->buttons;
    if (input_flags & 0x20) {
        if (actor->unk_16 == 1) {
            tile_id = read_map_cell_at_world_position(position->x.w.i, position->y.w.i);
            if (check_masked_value_in_current_range((u16)tile_id) != 0 &&position->z.v > 0) {
                init_input_angle_random_timer_action((struct TownObjectRecord *)(actor), (position), sprite);
                return;
            } else {
                init_ground_input_fallback((s32 * *)(actor), position, sprite);
                return;
            }
        } else {
            initialize_randomized_object_action((struct TownObjectRecord *)(actor), (position), sprite);
            store_input_angle(actor);
            accelerate_toward_input_angle((position));
            return;
        }
        return;
    }

    if (input_flags & 0xF000) {
        remaining_count = ((u16)actor->unk_3E) - 1;
        actor->unk_3E = remaining_count;
        play_periodic_sound(remaining_count, 12);
        store_input_angle(actor);
        accelerate_toward_input_keep_speed(position);
        damp_velocity_toward_input_limits(position);
        return;
    } else {
        initialize_scene_action_record(actor, position, sprite);
    }
}
