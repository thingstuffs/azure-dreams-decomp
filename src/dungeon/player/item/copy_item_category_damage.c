#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "shared/record_ptrs.h"
#include "dungeon/player/item.h"

extern u8 D_800DD704[];

/* Copy the current entry attribute and set damage from the item category damage table. */
void copy_item_category_damage(u8 *entry, DungeonItemEntry *item) {
    entry[3] = ((u8 *) primary_actor_record)[3];
    entry[0x26] = D_800DD704[item->kind];
}
