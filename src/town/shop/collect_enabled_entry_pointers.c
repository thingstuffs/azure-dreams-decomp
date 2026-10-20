#include "common.h"

typedef struct S_800B2964_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800B2964_0;

/* Collect pointers to enabled entries and terminate the list with 0. */
void collect_enabled_entry_pointers(s32 *entries, s32 entry_count) {
    s32 *output;
    s8 *entry;
    s32 entry_index;

    output = entries;
    entry_index = 0;
    if (entry_count > 0) {
        entry = (s8 *)0x80011F80;
        do {
            if (((S_800B2964_0 *)entry)->unk_01 != 0) {
                *output = (s32) entry;
                output += 1;
            }
            entry_index += 1;
            entry += 4;
        } while (entry_index < entry_count);
    }
    *output = 0;
}
