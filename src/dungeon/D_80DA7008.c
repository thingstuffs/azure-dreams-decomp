#include "common.h"

extern void dungeonDispatchAbilityAction(void);

/* jump_table; owner: dungeon/func_80DA7668. */
const u32 D_80158808[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonDispatchAbilityAction + 0x3A0),
    (u32)((u8 *)dungeonDispatchAbilityAction + 0x3A0),
    (u32)((u8 *)dungeonDispatchAbilityAction + 0x3A0),
    (u32)((u8 *)dungeonDispatchAbilityAction + 0x3CC),
    (u32)((u8 *)dungeonDispatchAbilityAction + 0x34C),
    (u32)((u8 *)dungeonDispatchAbilityAction + 0x34C),
    (u32)((u8 *)dungeonDispatchAbilityAction + 0x34C),
    (u32)((u8 *)dungeonDispatchAbilityAction + 0x2DC),
    (u32)((u8 *)dungeonDispatchAbilityAction + 0x2CC),
    (u32)((u8 *)dungeonDispatchAbilityAction + 0x3CC),
    (u32)((u8 *)dungeonDispatchAbilityAction + 0x3CC),
    (u32)((u8 *)dungeonDispatchAbilityAction + 0x390)
};
