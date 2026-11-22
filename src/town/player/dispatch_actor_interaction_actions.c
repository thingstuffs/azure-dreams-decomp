#include "town/scene/collision.h"
#include "town/player/init_movement_action.h"
#include "town/player/initialize_record_and_select_active_data.h"
#include "script_symbols.h"
#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "records/Rec_func_8009431C_arg0.h"
#include "town.h"
#include "town/player.h"
#include "town/player/motion.h"

#include "engine/object/test_resident_bitmap_bit_api.h"                         /* extern */
#include "town/player/coordinates.h"
#include "shared/sprite_frame_state.h"
void submit_object_resource_data();                         /* extern */
struct TownObjectRecord;      /* extern */
#include "shared/town_object.h"
struct TownObjectRecord; struct ObjectPosition; void initialize_actor_action_state(struct TownObjectRecord *, struct ObjectPosition *, struct SpriteFrameState *);     /* extern */
struct TownObjectRecord;      /* extern */
void initialize_actor_movement_interaction_action(s32 **record, void *ptr, void *ptr2);     /* extern */
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"                      /* extern */
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"                      /* extern */
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"      /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"                      /* extern */
extern ColliderView town_actor_control;

/* Update the actor and dispatch town actions from input and interaction state. */
void dispatch_actor_interaction_actions(Rec_func_8009431C_arg0 *actor, ObjectPosition *record, SpriteFrameState *sprite) {
    s16 height;
    s32 action_result;
    s32 interaction_result;
    u8 *page_base;
    s32 *height_data;
    GameWork *input_state = &g_game_work;

    resolve_collision_axis_order(record);
    apply_velocity_friction(record);
    {
        void *height_record = record;

        height_data = &position_query_scratch;
        height = query_capped_surface_height(height_record, height_data);
    }
    if ((height - record->z.w.i) >= 4) {
        if (town_action_state_flag == 0) {
            initialize_action_object(actor, record, sprite);
            return;
        }
    } else if (town_action_state_flag == 0) {
        set_height_and_slope_velocity((record), height, (struct TownVec * *)(height_data));
    }
    if ((input_state->pressed_buttons) & 0x10) {
        initialize_actor_action_state((struct TownObjectRecord *)(actor), (record), sprite);
        return;
    }
    if ((input_state->pressed_buttons) & 0x40) {
        action_result = select_adjacent_source_entry(actor, &town_actor_control);
        if (action_result != 0) {
            if (action_result == 2) {
                initialize_actor_movement_interaction_action(actor, record, sprite);
                return;
            }
            initialize_action_object_with_counter(actor, record, sprite);
            return;
        }
        if (test_resident_bitmap_bit(F_t_attack_enable) != 0) {
            init_threshold_countdown_action(actor, record, sprite);
            return;
        }
    } else {
            interaction_result = select_entry_by_input_direction(&town_actor_control);
        if (interaction_result != 0) {
            if (interaction_result == -1) {
                store_input_angle(actor);
                initialize_record_and_select_active_data(actor, (record), sprite);
                actor->unk_2C = 0;
                submit_object_resource_data(town_actor_control.selected_entry);
                return;
            }
            init_movement_action((struct TownObjectRecord *)(actor), record, sprite);
            return;
        }
        page_base = (u8 *)(u32)(input_state->buttons & 0xF000);
        if (page_base != 0) {
            initialize_motion_action((struct TownObjectRecord *)(actor), record, sprite);
        }
    }
}
