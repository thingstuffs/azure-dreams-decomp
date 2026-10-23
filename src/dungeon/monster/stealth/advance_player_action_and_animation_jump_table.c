#include "common.h"

extern void advance_player_action_and_animation(void);

/* jump_table; owner: dungeon/func_80F2F2A8. */
const u32 stealth_slot_a_action_targets_b[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_player_action_and_animation + 0x11C),
    (u32)((u8 *)advance_player_action_and_animation + 0x114),
    (u32)((u8 *)advance_player_action_and_animation + 0x10C),
    (u32)((u8 *)advance_player_action_and_animation + 0x124),
    (u32)((u8 *)advance_player_action_and_animation + 0xCC),
    (u32)((u8 *)advance_player_action_and_animation + 0xC4),
    (u32)((u8 *)advance_player_action_and_animation + 0xBC)
};
