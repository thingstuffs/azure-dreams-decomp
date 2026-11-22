#include "common.h"
#include "shared/dungeon_item_entries.h"

#include "engine/town.h"

void del_t_item_w_ptr(DungeonItemEntry *item);
extern s32 town_item_list; /* BYTES: the typed form changes the compiled bytes; the scalar view keeps the small-data load. */

/* Process the global value repeatedly until it becomes zero. */
void delete_all_town_items(void) {
    if (town_item_list != 0) {
        do {
            del_t_item_w_ptr(*(DungeonItemEntry **)0x8001029C);
        } while (*(DungeonItemEntry **)0x8001029C != 0);
    }
}
