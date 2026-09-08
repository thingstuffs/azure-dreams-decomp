#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A6620();          /* extern */
extern M2C_UNK D_80010248;

typedef struct S_800F6514_0 {
    u8 unk_00;
    u8 unk_01;
} S_800F6514_0;   /* var_s0 in func_800F6514 */

/* Process entries whose first two bytes are 2 and 0x13 in the 20-entry table. */
void func_800F6514(void) {
    M2C_UNK *entry;
    s32 entry_index;

    entry = (M2C_UNK *) 0x80010248;
    entry_index = 0;
    do {
        if ((((S_800F6514_0 *)entry)->unk_01 == 0x13) && (((S_800F6514_0 *)entry)->unk_00 == 2)) {
            func_800A6620(entry, 1);
        }
        entry_index += 1;
        entry += 1;
    } while (entry_index < 0x14);
}

/* MECHANISM: A fixed-address pointer literal forces retail's lui/ori base construction.
   Advancing one M2C_UNK element gives the four-byte loop stride while preserving
   the seed's 0x28 frame, saved-register hold set, and delay-slot CFG. */
