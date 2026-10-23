#include "common.h"

extern void dispatch_ability_action(void);

/* jump_table; owner: dungeon/func_80DA7668. */
const u32 dreamin_slot_c_behavior_targets[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)dispatch_ability_action + 0x3A0),
    (u32)((u8 *)dispatch_ability_action + 0x3A0),
    (u32)((u8 *)dispatch_ability_action + 0x3A0),
    (u32)((u8 *)dispatch_ability_action + 0x3CC),
    (u32)((u8 *)dispatch_ability_action + 0x34C),
    (u32)((u8 *)dispatch_ability_action + 0x34C),
    (u32)((u8 *)dispatch_ability_action + 0x34C),
    (u32)((u8 *)dispatch_ability_action + 0x2DC),
    (u32)((u8 *)dispatch_ability_action + 0x2CC),
    (u32)((u8 *)dispatch_ability_action + 0x3CC),
    (u32)((u8 *)dispatch_ability_action + 0x3CC),
    (u32)((u8 *)dispatch_ability_action + 0x390)
};
