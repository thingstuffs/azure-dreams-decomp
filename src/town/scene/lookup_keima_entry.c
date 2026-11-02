#include "town/scene/entry_requests.h"
#include "town/scene.h"
#include "town/data.h"

/* This overlay's placed copies of apply_entry_position (0x80016D10) and
 * resolve_entry_flag (0x80016C58).  Their names bind to the home copies, not
 * these placements, so the calls keep the addresses. */
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
        result = apply_entry_position(lookup_data, keima_flag_conditions, context, entry_code);
        if (entry_code == 50) {
            if (resolve_entry_flag(lookup_data, context, 50) != 0) {
                return D_80018640;
            }
        }
    }
    if (entry_code == 21) {
        if (resolve_entry_flag(keima_entries, context, 21) != 0) {
            return D_80018C7E;
        }
    }
    return result;
}
