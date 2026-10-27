#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "town/person/effects.h"
#include "town/player/coordinates.h"
struct TownObj;
struct TownVec;

typedef struct TownObject {
    u8 pad0[0xA];
    s16 limit;
    u8 padC[8];
    s32 state;
} TownObject;

extern void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(TownObject *arg);
extern void store_the_valid_shared_angle_in_offset_hex_10(void *arg);
extern void handle_adjust_vector_toward_selected_angle_limit_magnitude(TownObject *arg);
extern void select_sound_command_from_mode(void);
extern void compute_and_clamps_vector_based_adjustment_updates_town(struct TownObj *obj, s32 base_value, struct TownVec **vec_ptr);
extern void clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(TownObject *arg);
extern void initialize_scene_action_record(void *context, TownObject *object, s32 update_arg);
extern void add_hex_20000_s_signed_offset_hex_14(TownObject *arg);


/* Updates a town object based on its table value, limit, and a global flag. */
void update_threshold_bound_object(void *context, TownObject *object, s32 update_arg)
{
    s16 table_value;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(object);
    store_the_valid_shared_angle_in_offset_hex_10(context);
    handle_adjust_vector_toward_selected_angle_limit_magnitude(object);
    table_value = select_the_smaller_position_query_result_capped_n_64_writes_associated(object, ((s32 *)&position_query_scratch));

    if (object->limit >= table_value) {
        select_sound_command_from_mode();
        compute_and_clamps_vector_based_adjustment_updates_town(object, table_value, ((s32 *)&position_query_scratch));
        spawn_person_radial_effects(object);
        initialize_scene_action_record(context, object, update_arg);
    } else if (town_action_state_flag != 0) {
        select_sound_command_from_mode();
        object->state = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(object);
        initialize_scene_action_record(context, object, update_arg);
    } else {
        add_hex_20000_s_signed_offset_hex_14(object);
    }
}
