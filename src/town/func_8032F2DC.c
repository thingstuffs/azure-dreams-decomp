#include "shared/town_root.h"
#include "common.h"
#include "shared/record_ptrs.h"


typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))



/* Return the first entry index matching both bytes, or -1 if none matches. */
s32 func_80019ADC(s32 match_byte_1, s32 match_byte_0) {
    s32 result;
    s32 entry_index;
    void **entry_slot;
    TownStateRecord *list_owner;
    TownListEntry *entry;

    result = -1;
    list_owner = D_80016000->unk_38;
    entry_slot = list_owner->entries;
    entry_index = 0;
    if (list_owner->entries[0] != 0) {
        while (1) {
            entry = *entry_slot;
            if ((entry->gridY == match_byte_1) &&
                (entry->gridX == match_byte_0)) {
                result = entry_index;
                break;
            }
            entry_slot = (void **)((s8 *)entry_slot + 4);
            entry_index += 1;
            if (*entry_slot == 0) {
                return result;
            }
        }
    }
    return result;
}
