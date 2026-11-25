#ifndef DUNGEON_MENU_STATE_H
#define DUNGEON_MENU_STATE_H

/* Function contracts owned by src/dungeon/menu/state/ (decision 74; maintained by tools/headers). */
#include "common.h"
struct DungeonItemEntry;

/* Item selection at the tail of the reference tile object. Request 12 uses
 * the item word to pass a familiar slot index to the player dispatcher. */
typedef struct DungeonMenuItemSelection {
    struct DungeonItemEntry *item;
    struct DungeonItemEntry *secondary_item;
    s32 request;
} DungeonMenuItemSelection;

extern DungeonMenuItemSelection selected_item_record_alias;

void clear_dungeon_menu_flag(void);
void set_dungeon_menu_flag_if_idle(void);


#endif
