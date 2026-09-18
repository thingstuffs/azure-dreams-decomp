#include "common.h"
extern u8 D_800E3DB0[];

/* Return whether one of six entries matches the ID, treating 0x39 as 2. */
s32 func_800A15B0(s16 entry_id) {
    s16 match_id = entry_id;
    u8 *entry = D_800E3DB0;
    s16 index;

    if (entry_id == 0x39) match_id = 2;
    for (index = 0; index < 6; index++, entry += 8) {
        if (entry[1] != match_id) {
            continue;
        }
        return 1;
    }
    return 0;
}
