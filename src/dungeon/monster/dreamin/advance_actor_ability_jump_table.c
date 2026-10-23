#include "common.h"

extern void advance_actor_ability(void);

/* jump_table; owner: dungeon/func_80D97070. */
const u32 dreamin_slot_f_action_targets[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_actor_ability + 0x11C),
    (u32)((u8 *)advance_actor_ability + 0x114),
    (u32)((u8 *)advance_actor_ability + 0x10C),
    (u32)((u8 *)advance_actor_ability + 0x124),
    (u32)((u8 *)advance_actor_ability + 0xCC),
    (u32)((u8 *)advance_actor_ability + 0xC4),
    (u32)((u8 *)advance_actor_ability + 0xBC)
};
