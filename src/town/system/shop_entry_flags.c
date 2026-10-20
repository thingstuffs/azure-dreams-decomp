/* Toggle shop entry flags and sum the values of selected entries. */

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AD7F8_arg0.h"



typedef struct S_800AD7F8_1 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800AD7F8_1;

/* Toggle the selected entry flag 0x20 when flag 0x80 is clear. */
extern s32 func_8004A618(u8 *);
extern s32 func_8004A638(u8 *);

void toggle_selected_entry_flag(Rec_func_800AD7F8_arg0 *state) {
    u8 flags;
    S_800AD7F8_1 *entry;

    entry = (state->unk_04 * 4) + state->unk_20;
    flags = entry->unk_03;
    if (!(flags & 0x80)) {
        entry->unk_03 = (u8) (flags ^ 0x20);
    }
}


/* Sum results for flagged entries using the selected mode. */
s32 sum_flagged_entry_values(u8 *entry, s32 mode) {
    register s32 total;

    total = 0;
    if (entry[1] != 0) {
        do {
            if (entry[3] & 0x20) {
                if (mode == 0) {
                    total += func_8004A638(entry);
                } else {
                    total += func_8004A618(entry);
                }
            }
            entry += 4;
        } while (entry[1] != 0);
    }
    return total;
}
