#include "common.h"

extern void advance_actor_ability_and_completion(void);

/* jump_table; owner: dungeon/func_80ADFA30. */
const u32 saber_slot_c_extra_action_targets[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_actor_ability_and_completion + 0x11C),
    (u32)((u8 *)advance_actor_ability_and_completion + 0x114),
    (u32)((u8 *)advance_actor_ability_and_completion + 0x10C),
    (u32)((u8 *)advance_actor_ability_and_completion + 0x124),
    (u32)((u8 *)advance_actor_ability_and_completion + 0xC8),
    (u32)((u8 *)advance_actor_ability_and_completion + 0xC0),
    (u32)((u8 *)advance_actor_ability_and_completion + 0xB8)
};
