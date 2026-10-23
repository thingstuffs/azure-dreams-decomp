#include "shared/town_root.h"
#include "common.h"
#include "shared/record_ptrs.h"


/* Count entries in the zero-terminated table. */
s32 count_town_items(void) {
    s32 *entry;
    s32 count;
    TownStateRecord *table;

    table = town_scene_root->town_state;
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
