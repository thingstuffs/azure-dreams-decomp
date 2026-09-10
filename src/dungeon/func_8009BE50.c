#include "common.h"
extern u8 D_800E3DB0[];

/* Return whether one of six entries matches the ID, treating 0x39 as 2. */
s32 func_800A15B0(s16 entry_id) {
    s16 match_id = entry_id;
    u8 *entry = D_800E3DB0;
    s16 index = 0;
    s16 next_index;

    if (entry_id == 0x39) match_id = 2;
    do {
        if (entry[1] != match_id) {
            next_index = index + 1;
            index = next_index;
            entry += 8;
        } else {
            return 1;
        }
    } while (next_index < 6);
    do {
        ASM_KEEP(index);
    } while (0);
    return 0;
}
