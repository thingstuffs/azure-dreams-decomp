#include "shared/position_query.h"
#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "town/player/coordinates.h"
#include "town/player.h"
#include "town/player/position.h"

#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"      /* extern */
#include "town/player/initialize_record_with_handler_table_api.h"        /* extern */


/* Advance the object's position and handle crossing the sampled limit. */
void advance_player_position(s32 context, EntityRec *object, s32 update_data) {
    s16 limit;

    object->z.v = (s32) (object->z.v + object->flags14);
    limit = select_the_smaller_position_query_result_capped_n_64_writes_associated(object, &position_query_scratch);
    if (limit < object->z.w.i) {
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(object), limit, (struct TownVec * *)(&position_query_scratch));
        initialize_record_with_handler_table((Struct8009B1C8 *)(context), (s32)(object), update_data);
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(object);
}
