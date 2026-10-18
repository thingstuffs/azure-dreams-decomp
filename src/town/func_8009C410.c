#include "shared/position_query.h"
#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"

void add_hex_20000_s_signed_offset_hex_14();                 /* extern */
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();               /* extern */
void compute_and_clamps_vector_based_adjustment_updates_town();      /* extern */
void initialize_record_with_handler_table();        /* extern */


/* Advance the object's position and handle crossing the sampled limit. */
void advance_player_position(s32 context, EntityRec *object, s32 update_data) {
    s16 limit;

    object->z.v = (s32) (object->z.v + object->flags14);
    limit = select_the_smaller_position_query_result_capped_n_64_writes_associated(object, &D_800FE488);
    if (limit < object->z.w.i) {
        compute_and_clamps_vector_based_adjustment_updates_town(object, limit, &D_800FE488);
        initialize_record_with_handler_table(context, object, update_data);
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(object);
}
