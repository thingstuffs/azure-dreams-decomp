#include "common.h"

extern void update_creature_action(void);

/* jump_table; owner: dungeon/func_8101D858. */
const void *const garuda_slot_c_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_creature_action + 0x494),
    ((u8 *)update_creature_action + 0x494),
    ((u8 *)update_creature_action + 0x494),
    ((u8 *)update_creature_action + 0x4C0),
    ((u8 *)update_creature_action + 0x440),
    ((u8 *)update_creature_action + 0x440),
    ((u8 *)update_creature_action + 0x440),
    ((u8 *)update_creature_action + 0x408),
    ((u8 *)update_creature_action + 0x3AC),
    ((u8 *)update_creature_action + 0x4C0),
    ((u8 *)update_creature_action + 0x4C0),
    ((u8 *)update_creature_action + 0x484)
};
