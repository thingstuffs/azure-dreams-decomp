#include "common.h"

extern s32 get_entity_effect_value(void *entry, s32 effect_id);
extern void clear_slots_of_type(void *object, s32 value);
extern void adjust_source_value_and_finalize(void *object, void *value);
extern s8 D_800E0DF5[];

/* Handle a nonzero type 2 query result and always return success. */
s32 handle_type_two_query_result(void *object) {
    if ((get_entity_effect_value(object, 2) << 16) != 0) {
        clear_slots_of_type(object, 2);
        adjust_source_value_and_finalize(object, D_800E0DF5);
        return 1;
    }
    return 1;
}
