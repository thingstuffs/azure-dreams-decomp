#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"

typedef struct {
    u8 pad0[0xA];
    s16 field_A;
    u8 padC[8];
    s32 field_14;
} TownObject;


extern void initialize_scene_action_record(void *, TownObject *, void *);
extern void store_the_valid_shared_angle_in_offset_hex_10(void *);
extern void handle_adjust_vector_toward_selected_angle_limit_magnitude(TownObject *);
extern void add_hex_20000_s_signed_offset_hex_14(TownObject *);
extern void clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(TownObject *);
extern s16 select_the_smaller_position_query_result_capped_n_64_writes_associated(TownObject *, void *);
extern void compute_and_clamps_vector_based_adjustment_updates_town(TownObject *, s16, void *);
extern void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(TownObject *);

/* Updates a town object based on its computed threshold and the global flag. */
void update_threshold_object(void *context, TownObject *object, void *update_data)
{
    s16 threshold;
    u8 *threshold_data;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(object);
    store_the_valid_shared_angle_in_offset_hex_10(context);
    handle_adjust_vector_toward_selected_angle_limit_magnitude(object);
    threshold_data = ((u8 *)&D_800FE488);
    threshold = select_the_smaller_position_query_result_capped_n_64_writes_associated(object, threshold_data);

    if (object->field_A >= threshold) {
        compute_and_clamps_vector_based_adjustment_updates_town(object, threshold, threshold_data);
        initialize_scene_action_record(context, object, update_data);
        return;
    }

    if (D_800CFCEF != 0) {
        object->field_14 = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(object);
        initialize_scene_action_record(context, object, update_data);
    } else {
        add_hex_20000_s_signed_offset_hex_14(object);
    }
}
