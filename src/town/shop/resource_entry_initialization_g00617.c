/* Resource entry initialization (G00617). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B5204. */
#include "town/shop/resource_entry_initialization_g00617.h"

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

/* Counts entries in a zero-terminated integer array. */
s32 count_nonzero_entries(s32 *entries) {
    s32 *entry;
    s32 count;

    entry = entries;
    count = 0;
    if (*entry != 0) {
        do {
            entry += 1;
            count += 1;
        } while (*entry != 0);
    }
    return count;
}

/* Acquires a resource and initializes its associated state on success. */
s32 acquire_resource_and_initialize_state(void *state) {
    s32 resourceHandle;
    s32 resourceConfig;

    resourceHandle = create_callback_pair_default(0x100);
    ((S_800B29D0_0 *)state)->unk_40 = resourceHandle;
    if (resourceHandle != 0) {
        resourceConfig = get_mode_selected_value();
        ((S_800B29D0_0 *)state)->unk_44 = resourceConfig;
        collect_enabled_entry_pointers((s32 *)(((S_800B29D0_0 *)state)->unk_40), resourceConfig);
        ((S_800B29D0_0 *)state)->unk_38 = count_nonzero_entries((s32 *)(((S_800B29D0_0 *)state)->unk_40));
        get_zero_based_group_index(state + 0x2C);
    }
    return ((S_800B29D0_0 *)state)->unk_40;
}
