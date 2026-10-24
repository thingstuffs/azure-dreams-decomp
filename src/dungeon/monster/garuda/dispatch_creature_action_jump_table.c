#include "common.h"

extern void dispatch_creature_action(void);

/* jump_table; owner: dungeon/func_8100B858. */
const void *const garuda_slot_f_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)dispatch_creature_action + 0x494),
    ((u8 *)dispatch_creature_action + 0x494),
    ((u8 *)dispatch_creature_action + 0x494),
    ((u8 *)dispatch_creature_action + 0x4C0),
    ((u8 *)dispatch_creature_action + 0x440),
    ((u8 *)dispatch_creature_action + 0x440),
    ((u8 *)dispatch_creature_action + 0x440),
    ((u8 *)dispatch_creature_action + 0x408),
    ((u8 *)dispatch_creature_action + 0x3AC),
    ((u8 *)dispatch_creature_action + 0x4C0),
    ((u8 *)dispatch_creature_action + 0x4C0),
    ((u8 *)dispatch_creature_action + 0x484)
};
