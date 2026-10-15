#include "modules/dungeon_town_load.h"

s32 func_8008B328(void) {
    s32 slot;
    u8 *entry_indices;
    s32 *entries;
    s32 any_found;

    slot = 0;
    entry_indices = D_800CF828;
    entries = D_800CF838;
    for (; slot < 0xF; slot++) {
        s32 found = func_8008B2E4(entries[*(u8 *)((u32)slot + (u32)entry_indices)]);

        if (found != 0) {
            any_found = 1;
            return any_found;
        }
    }
    any_found = 0;
    return any_found;
}
