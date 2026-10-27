#include "shared/position_query.h"
#include "common.h"
#include "town/player/coordinates.h"

extern void compute_and_clamps_vector_based_adjustment_updates_town(void *obj, s16 base_value, void *vec_ptr);
extern void initialize_record_with_handler_table(void *record, void *setup_value, s32 init_value);

extern u8 town_actor_control[];

/* Conditionally refreshes object data before passing it to initialize_record_with_handler_table. */
void refresh_object_position_and_initialize(void *context, void *object, s32 mode) {
    void *state;

    if (town_actor_control[0x3B] != 0) {
        state = *(void **)(*(void **)(town_actor_control + 0x20) + 8);
        if ((*(s32 *)((u8 *)state + 0xC) != 0) ||
            (*(s32 *)((u8 *)state + 0x10) != 0) ||
            (*(s32 *)((u8 *)state + 0x14) != 0)) {
            compute_and_clamps_vector_based_adjustment_updates_town(object, select_the_smaller_position_query_result_capped_n_64_writes_associated(object, &position_query_scratch),
                          &position_query_scratch);
        }
    } else {
        compute_and_clamps_vector_based_adjustment_updates_town(object, select_the_smaller_position_query_result_capped_n_64_writes_associated(object, &position_query_scratch),
                      &position_query_scratch);
    }
    initialize_record_with_handler_table(context, object, mode);
}
