#include "common.h"
#include "shared/types3a_types.h"


/* Returns the index of the first matching value pair, or 20 if none matches. */
int func_8004A6C0(int first_value, int second_value) {
    int entry_index;
    for (entry_index = 0; entry_index < 20; entry_index++) {
        s32 offset = entry_index * sizeof(ResourceCategoryPair);
        if (((ResourceCategoryPair *)(offset + 0x80013564))->a == first_value
            && ((ResourceCategoryPair *)(offset + 0x80013564))->b == second_value)
            break;
    }
    return entry_index;
}
