#include "common.h"

typedef struct {
    s32 flag;
    u16 status;
    u16 pad6;
} S_80083D08;

extern S_80083D08 D_80083D08[6];

/* Sets status bit 0 for each entry with a nonzero flag. */
void func_800481E0(void) {
    s32 entry_index;

    for (entry_index = 0; entry_index < 6; entry_index++) {
        S_80083D08 *entry = &D_80083D08[entry_index];
        if (entry->flag) {
            entry->status |= 1;
        }
    }
}
