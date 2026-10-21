/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void add_hex_20000_s_signed_offset_hex_14();                 
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();               
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"
void bind_default_data_and_clear_record();        

void adjust_object_motion_at_threshold(s32 context, EntityRec *record, s32 action_data) {
    s16 threshold;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(record);
    threshold = select_the_smaller_position_query_result_capped_n_64_writes_associated(record, &position_query_scratch);
    if (record->z.w.i >= threshold) {
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(record), threshold, (struct TownVec * *)(&position_query_scratch));
        bind_default_data_and_clear_record(context, record, action_data);
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(record, threshold);
}
