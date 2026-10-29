#ifndef DUNGEON_PLAYER_ITEM_H
#define DUNGEON_PLAYER_ITEM_H

/* Function contracts owned by src/dungeon/player/item/ (decision 74; maintained by tools/headers). */
#include "common.h"

struct DungeonItemEntry;
void begin_deferred_item_action(void *record_data, void *unused_position, void *unused_sprite, void *unused_actor);
void *begin_holding_item(void *actor, void *action, void *target, void *item);
void copy_item_category_damage(u8 *entry, struct DungeonItemEntry *item);
void snapshot_inventory_familiar_records(void);
void begin_deferred_player_item_effect(void *object, unsigned long unused_1, void *unused_2, void *mode);


/* The final context is null for state 0x2D; a non-null context selects 0x2C. */
void begin_mode_selected_item_action(void *object_data, void *unused_1, void *unused_2, void *mode);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct Ctx;
struct Item;
struct Unit;
s32 collect_ground_item(struct Ctx *ctx, char *text, struct Item *item, struct Unit *unit);

#endif
