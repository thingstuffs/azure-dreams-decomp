#include "common.h"
#include "town/scene/state_data.h"
#include "town/scene/choice_data.h"
#include "town/scene.h"

typedef struct TownEntry {
    s32 unk0;
    s32 unk4;
    s32 choice_data;
    s32 unkC;
} TownEntry;

typedef struct TownContext {
    u8 pad0[0x10];
    TownEntry *entries;
} TownContext;

s32 select_next_eligible_wrapped_entry(void);

/* Selects a value with a fallback and stores its converted result in the town entry. */
s32 pick_enabled_entry_choice(TownContext *context, s32 entry_index) {
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

    entry_value = (s32)(unsigned long)copy_indexed_entry_value(selected_value);
    scene_choice_index = selected_value;
    context->entries[entry_index].choice_data = entry_value;
    return 0;
}
