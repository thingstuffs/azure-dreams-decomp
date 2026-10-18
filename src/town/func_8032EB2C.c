#include "shared/town_root.h"
#include "common.h"
#include "shared/record_ptrs.h"


/* Count entries in the zero-terminated table. */
s32 count_shop_entries(void) {
    s32 *entry;
    s32 count;
    TownStateRecord *table;

    table = D_80016000->unk_38;
    entry = (s32 *)table->entries;
    count = 0;
    if (*(s32 *)table->entries != 0) {
        do {
            entry++;
            count++;
        } while (*entry != 0);
    }
    return count;
}
