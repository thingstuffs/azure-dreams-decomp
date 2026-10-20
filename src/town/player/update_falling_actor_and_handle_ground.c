#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void add_hex_20000_s_signed_offset_hex_14();                 /* extern */
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();               /* extern */
void compute_and_clamps_vector_based_adjustment_updates_town();      /* extern */
void initialize_record_with_handler_table();        /* extern */


/* Update the actor's fall and handle contact with the ground. */
void update_falling_actor_and_handle_ground(s32 context, EntityRec *actor, s32 action_arg) {
    s16 ground_height;

    ground_height = select_the_smaller_position_query_result_capped_n_64_writes_associated(actor, &D_800FE488);
    if (actor->z.w.i >= ground_height) {
        compute_and_clamps_vector_based_adjustment_updates_town(actor, ground_height, &D_800FE488);
        initialize_record_with_handler_table(context, actor, action_arg);
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(actor);
}
