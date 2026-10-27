#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "town/player/coordinates.h"

void add_hex_20000_s_signed_offset_hex_14(); /* Unprototyped: one or two arguments; retail reads only the first. */                 /* extern */
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"      /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"                      /* extern */
void bind_handler_and_initialize_entity(); /* Slot contract: loading images do not establish one callee contract. */        /* extern */


/* Updates the record and selects a handler based on its computed threshold. */
void update_actor_and_select_ground_handler(s32 context, EntityRec *record, s32 action_data) {
    s16 threshold;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(record);
    threshold = select_the_smaller_position_query_result_capped_n_64_writes_associated(record, &position_query_scratch);
    if (record->z.w.i >= threshold) {
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(record), threshold, (struct TownVec * *)(&position_query_scratch));
        bind_handler_and_initialize_entity(context, record, action_data);
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(record);
}
