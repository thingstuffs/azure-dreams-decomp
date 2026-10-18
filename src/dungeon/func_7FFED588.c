#include "modules/dungeon_ovl_d54c.h"

s32 sum_resource_bytes(s32 entry_count) {
    s32 sum;
    s32 entry_index;

    sum = 0;
    for (entry_index = 0; entry_index < entry_count; entry_index++) {
        sum += D_800CF720[entry_index].field_4;
    }
    return sum;
}
