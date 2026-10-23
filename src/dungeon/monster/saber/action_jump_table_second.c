#include "common.h"

extern void advance_attack_with_delayed_sprite_flash(void);

/* jump_table; owner: dungeon/func_80AD97D8. */
const u32 saber_slot_d_action_targets_b[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_attack_with_delayed_sprite_flash + 0x48),
    (u32)((u8 *)advance_attack_with_delayed_sprite_flash + 0x98),
    (u32)((u8 *)advance_attack_with_delayed_sprite_flash + 0x10C),
    (u32)((u8 *)advance_attack_with_delayed_sprite_flash + 0x180),
    (u32)((u8 *)advance_attack_with_delayed_sprite_flash + 0x1F8)
};
