#ifndef DUNGEON_PLAYER_ITEM_H
#define DUNGEON_PLAYER_ITEM_H

/* Function contracts owned by src/dungeon/player/item/ (decision 74; maintained by tools/headers). */
#include "common.h"
void *begin_holding_item(void *actor, s32 action, void *target, void *item);
void copy_item_category_damage(u8 *entry, u8 *item);
void snapshot_inventory_familiar_records(void);


#endif
