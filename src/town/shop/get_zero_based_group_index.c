#include "common.h"
#include "town/shop.h"
#include "town/shop/group_index.h"


/* Convert the stored value to a zero-based group of ten, preserving zero. */
void get_zero_based_group_index(TownGroupIndex *record) {
    s32 stored_value = record->value;

    if (stored_value != 0) {
        record->index = (stored_value - 1) / 10;
        return;
    }
    record->index = 0;
}
