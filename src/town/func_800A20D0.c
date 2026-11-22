/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "town/shop/item_lookup.h"
#include "shared/town_state.h"
#include "town.h"

#ifndef NULL
#define NULL 0
#endif

/* Returns the first carried item matching both kind and type, or NULL when no item matches. */
DungeonItemEntry *find_item_by_kind_and_type(s32 item_kind, s32 item_type) {
    TownStateRecord *table;
    DungeonItemEntry *item;
    s32 i;

    table = (TownStateRecord *)0x80010000;
    for (i = 0; table->entries[i] != NULL; i++) {
        item = table->entries[i];
        if ((item->unk_00 == item_kind) && (item->kind == item_type)) {
            return item;
        }
    }
    return NULL;
}
