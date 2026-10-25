#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void add_hex_20000_s_signed_offset_hex_14(EntityRec *record);                 /* extern */
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();               /* extern */
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"      /* extern */
#include "town/player/initialize_record_with_handler_table_api.h"        /* extern */


/* Update the actor's fall and handle contact with the ground. */
void update_falling_actor_and_handle_ground(s32 context, EntityRec *actor, s32 action_arg) {
    s16 ground_height;

    ground_height = select_the_smaller_position_query_result_capped_n_64_writes_associated(actor, &position_query_scratch);
    if (actor->z.w.i >= ground_height) {
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(actor), ground_height, (struct TownVec * *)(&position_query_scratch));
        initialize_record_with_handler_table((Struct8009B1C8 *)(context), (s32)(actor), action_arg);
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(actor);
}
