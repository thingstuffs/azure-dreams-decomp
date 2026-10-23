#include "script_symbols.h"
#include "common.h"

extern u8 D_800189CC[16];
extern u8 scene_event_lookup_context[16];
extern u8 D_8001A3AE[];
extern u8 D_8001A495[];

extern void check_ready_or_run_followup(void);
extern s32 func_800178A8(void *, s32, s32);
extern void *func_80017960(void *, void *, s32, s32);
extern void initialize_state_two_entries_pointer(s32);
extern s32 func_8001868C(s32);

/* Looks up an entry and applies special-case overrides for selectors 0xB and 0x1C. */
void *lookup_entry_with_selector_overrides(s32 entry_id, s32 unused_arg, s32 selector)
{
    void *entry_data;
    u8 *entry_table;

    entry_table = D_800189CC;
    entry_data = func_80017960(entry_table, scene_event_lookup_context, entry_id, selector);
    if (selector == 0xB) {
        check_ready_or_run_followup();
        if (func_800178A8(entry_table, entry_id, 0xB) != 0) {
            return D_8001A3AE;
        }
        return entry_data;
    }
    if (selector == 0x1C) {
        if (func_8001868C(F_sbs34_pad18) == 0) {
            initialize_state_two_entries_pointer(F_sbs34_pad18);
            return D_8001A495;
        }
    }
    return entry_data;
}
