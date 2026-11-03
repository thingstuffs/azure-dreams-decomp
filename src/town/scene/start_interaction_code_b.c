#include "common.h"

typedef struct TownEntry {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} TownEntry;

typedef struct TownContext {
    u8 pad0[0x10];
    TownEntry *entries;
} TownContext;

s32 count_enabled_town_entries(void);
s32 copy_indexed_entry_value(s32);
s32 find_first_enabled_paired_entry(void);
s32 select_next_eligible_wrapped_entry(void);
extern s32 scene_update_state;
extern s32 scene_choice_index;

/* Selects a value with a fallback and stores its converted result in the town entry. */
s32 start_interaction_on_code_0x479(TownContext *context, s32 entry_index) {
    s32 selected_value;
    s32 entry_value;

    scene_update_state = 2;
    if (count_enabled_town_entries() == 0) {
        return 1;
    }

    selected_value = find_first_enabled_paired_entry();
    if (selected_value == 0) {
        selected_value = select_next_eligible_wrapped_entry();
    }

    entry_value = copy_indexed_entry_value(selected_value);
    scene_choice_index = selected_value;
    context->entries[entry_index].unk8 = entry_value;
    return 0;
}
