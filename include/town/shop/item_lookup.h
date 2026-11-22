#ifndef TOWN_SHOP_ITEM_LOOKUP_H
#define TOWN_SHOP_ITEM_LOOKUP_H

#include "shared/dungeon_item_entries.h"

int get_item_chk(void);
struct ObjectPosition;
struct SpriteFrameState;
int remove_object_if_item_found(void *object, void *subject, struct ObjectPosition *motion,
                                struct SpriteFrameState *sprite, int *work);
DungeonItemEntry *find_item_by_kind_and_type(int item_kind, int item_type);
int find_first_vacant_record(const unsigned char *records, int count);

int find_slot_index_by_address(DungeonItemEntry *target, DungeonItemEntry *slots, int slot_count);

/* The 84-byte encoded slot snapshot stores resolved slot indices at +0x4C and +0x4D. */
typedef struct S_800422DC_Self {
    unsigned char  pad0[0x4C];
    unsigned char  f4C;
    unsigned char  f4D;
    unsigned char  pad4E[2];
    int f50;
} TownSlotSnapshot;

extern TownSlotSnapshot town_slot_snapshot;

#endif
