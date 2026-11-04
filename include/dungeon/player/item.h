#ifndef DUNGEON_PLAYER_ITEM_H
#define DUNGEON_PLAYER_ITEM_H

/* Function contracts owned by src/dungeon/player/item/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/entity.h"

struct DungeonItemEntry;
struct SpriteFrameState;
void begin_deferred_item_action(void *record_data, void *unused_position, void *unused_sprite, void *unused_actor);
void *begin_holding_item(void *actor, void *action, void *target, void *item);
void copy_item_category_damage(u8 *entry, struct DungeonItemEntry *item);
void snapshot_inventory_familiar_records(void);
void begin_deferred_player_item_effect(void *object, unsigned long unused_1, void *unused_2, ActorRecord *actor);


/* The final context is null for state 0x2D; a non-null context selects 0x2C. */
void begin_mode_selected_item_action(void *object_data, void *unused_1, void *unused_2, void *mode);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct Ctx;
struct Item;
struct Unit;
s32 collect_ground_item(struct Ctx *ctx, char *text, struct Item *item, struct Unit *unit);

#include "records/Rec_func_8008ACDC_arg0.h"
s16 dispatch_selected_item_use(Rec_func_8008ACDC_arg0 *actor, s16 item_id, s16 other_item_id);


void update_item_target_selection(PlayerRecord *state, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite, ActorRecord *context);

void snapshot_inventory_and_familiars(void *input_state);

#endif
