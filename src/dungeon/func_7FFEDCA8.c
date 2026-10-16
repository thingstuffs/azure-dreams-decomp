#include "modules/dungeon_town_load.h"

void reserve_twch_load(s32 entry_id) {
    s32 entry_index;
    s32 found;

    found = townResourceValueTableContains(D_800CF838[entry_id]);
    entry_index = 0;
    if (found != 0) {
        entry_index = func_8008B3AC();
        if (entry_index >= 0) {
            D_800CF828[entry_index] = entry_id;
            return;
        }
        entry_index = 0;
    }

    do {
        if (D_800CF828[entry_index] == 0) {
            D_800CF828[entry_index] = entry_id;
            D_800CF828[entry_index + 1] = 0;
            return;
        }
        entry_index++;
    } while (entry_index < 15);
}
