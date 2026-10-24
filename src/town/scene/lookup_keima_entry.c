#include "town/scene/entry_requests.h"

/* This overlay's placed copies of apply_entry_position (0x80016D10) and
 * resolve_entry_flag (0x80016C58).  Their names bind to the home copies, not
 * these placements, so the calls keep the addresses. */
extern void *func_80016D10(void *entries, void *conditions, void *context, s32 selection);
extern s32 func_80016C58(void *entry_table, void *context, s32 entry_key);
extern u8 keima_entries[];
extern u8 keima_flag_conditions[];
extern u8 D_80018640[];
extern u8 D_80018C7E[];

/* Codes 50 and 21 select special records when the local entry check succeeds. */
void *lookup_keima_entry(void *context, s32 unused, s32 code)
{
    s32 entry_code;
    void *result;

    entry_code = code;
    {
        void *lookup_data = keima_entries;
        result = func_80016D10(lookup_data, keima_flag_conditions, context, entry_code);
        if (entry_code == 50) {
            if (func_80016C58(lookup_data, context, 50) != 0) {
                return D_80018640;
            }
        }
    }
    if (entry_code == 21) {
        if (func_80016C58(keima_entries, context, 21) != 0) {
            return D_80018C7E;
        }
    }
    return result;
}
