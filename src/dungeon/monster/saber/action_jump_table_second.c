#include "common.h"

extern void advance_attack_with_delayed_sprite_flash(void);

/* jump_table; owner: dungeon/func_80AD97D8. */
const void *const saber_slot_d_action_targets[5] __attribute__((aligned(4))) = {
    ((u8 *)advance_attack_with_delayed_sprite_flash + 0x48),
    ((u8 *)advance_attack_with_delayed_sprite_flash + 0x98),
    ((u8 *)advance_attack_with_delayed_sprite_flash + 0x10C),
    ((u8 *)advance_attack_with_delayed_sprite_flash + 0x180),
    ((u8 *)advance_attack_with_delayed_sprite_flash + 0x1F8)
};
