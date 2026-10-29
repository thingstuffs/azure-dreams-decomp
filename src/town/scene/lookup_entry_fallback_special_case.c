#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"

extern s32 func_800178A8(void *table, s32 lookup_key, s32 entry_id);
extern void *func_80017960(void *table, void *fallback_table, s32 lookup_key, s32 entry_id);
extern void initialize_state_two_entries_pointer(s32 value);

extern u8 D_800189AC[16];
extern u8 scene_event_lookup_context[16];
extern u8 D_80018FFC[16];

/* Looks up an entry or selects a fallback, with a special case for entry 0x1C. */
void *lookup_entry_fallback_special_case(s32 lookup_key, s32 unused, s32 entry_id) {
    void *entry;

    entry = get_special_data_for_low_value_id(entry_id);
    if (entry != 0) {
        return entry;
    }
    initialize_state_two_entries_pointer(F_sb34_00);
    entry = func_80017960(&D_800189AC, &scene_event_lookup_context, lookup_key, entry_id);
    if ((entry_id == 0x1C) && (func_800178A8(&D_800189AC, lookup_key, 0x1C) != 0)) {
        entry = &D_80018FFC;
    }
    return entry;
}
