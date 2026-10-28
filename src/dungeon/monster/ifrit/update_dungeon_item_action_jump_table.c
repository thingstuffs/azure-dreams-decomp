#include "common.h"
#include "shared/entity.h"

extern void update_dungeon_item_action(void *action, ObjectPosition *motion, void *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80A250C4. */
const void *const ifrit_slot_f_action_cases[7] __attribute__((aligned(4))) = {
    ((u8 *)update_dungeon_item_action + 0x128),
    ((u8 *)update_dungeon_item_action + 0x120),
    ((u8 *)update_dungeon_item_action + 0x118),
    ((u8 *)update_dungeon_item_action + 0x130),
    ((u8 *)update_dungeon_item_action + 0xD8),
    ((u8 *)update_dungeon_item_action + 0xD0),
    ((u8 *)update_dungeon_item_action + 0xC8)
};
