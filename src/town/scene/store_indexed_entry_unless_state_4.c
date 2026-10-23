#include "common.h"

typedef struct TownStateEntry {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
} TownStateEntry;

typedef struct TownStateEntryTable {
    u8 pad_00[0x10];
    TownStateEntry *entries;
} TownStateEntryTable;

extern s32 func_80017F5C(s32);
extern s32 scene_update_state;
extern s32 scene_choice_index;

/*
 * Stores func_80017F5C of scene_choice_index in the selected entry unless scene_update_state is 4;
 * returns whether it stored a value.
 */
s32 unless_current_state_4_store(TownStateEntryTable *table, s32 index) {
    if (scene_update_state != 4) {
        table->entries[index].unk_08 = func_80017F5C(scene_choice_index);
        return 1;
    }
    return 0;
}
