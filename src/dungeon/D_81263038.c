#include "common.h"

extern void advance_overlay_actor_action(void);

/* jump_table; owner: dungeon/func_81264D6C. */
const u32 D_8015E838[9] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_overlay_actor_action + 0x64),
    (u32)((u8 *)advance_overlay_actor_action + 0x2A8),
    (u32)((u8 *)advance_overlay_actor_action + 0x2F0),
    (u32)((u8 *)advance_overlay_actor_action + 0x330),
    (u32)((u8 *)advance_overlay_actor_action + 0x3D0),
    (u32)((u8 *)advance_overlay_actor_action + 0x43C),
    (u32)((u8 *)advance_overlay_actor_action + 0x4A4),
    (u32)((u8 *)advance_overlay_actor_action + 0x4C4),
    (u32)((u8 *)advance_overlay_actor_action + 0x558)
};
