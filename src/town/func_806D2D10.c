#include "common.h"

extern void set_flag_test_indexed_bit();
extern void clear_indexed_flag_unless_identifier();
extern s32 select_data_array_based_flag();

/* Updates the target based on the source's state, then updates the source. */
void update_flag_test_target(s16 sourceId, s16 targetId) {
    if (select_data_array_based_flag(sourceId) != 0) {
        set_flag_test_indexed_bit(targetId);
    } else {
        clear_indexed_flag_unless_identifier(targetId);
    }
    set_flag_test_indexed_bit(sourceId);
}
