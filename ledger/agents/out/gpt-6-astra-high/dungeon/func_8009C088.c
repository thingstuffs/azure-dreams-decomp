#include "common.h"

extern u8 D_800E3DB0[];
extern u8 D_800E3DD0[];
extern u8 D_800E3DE0[];

/* Returns an entry selected by type and ID, or null if no match is found. */
u8 *func_800A17E8(s16 entry_id, s16 entry_type) {
    register s16 entry_index ASM_REG("$6");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *entry;
    s16 next_index;

    if (entry_type == 3) {
        entry = D_800E3DD0;
        entry_index = 4;
    } else if (entry_type == 2) {
        return D_800E3DE0;
    } else if (D_800E3DB0[0x11] == 0x38) {
        entry = D_800E3DB0 + 0x18;
        entry_index = 3;
    } else if (D_800E3DB0[9] == 0x31) {
        entry = D_800E3DB0 + 0x10;
        entry_index = 2;
    } else {
        entry = D_800E3DB0;
        entry_index = 0;
    }

    if (entry_index < 6) {
        do {
            if ((entry_type == 1 || entry_type == 3) && entry[0] != entry_type) {
                return 0;
            }
            if (entry[1] == entry_id) {
                return entry;
            }
            next_index = entry_index + 1;
            entry_index = next_index;
            entry += 8;
        } while (next_index < 6);
    }
    return 0;
}
