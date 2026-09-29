#include "common.h"

typedef struct TownEntry {
    s16 value;
    u8 pad_02[8];
} TownEntry;

extern TownEntry D_800D4094[];

/* Return the index of the matching value or the terminating zero in the entry table. */
s32 func_800C0F60(s32 target_value) {
    s32 entry_index;

    for (entry_index = 0; D_800D4094[entry_index].value != 0; entry_index++) {
        if (D_800D4094[entry_index].value == target_value) {
            break;
        }
    }
    return entry_index;
}
