#include "common.h"

extern void advance_flashing_sprite_sequence(void);

/* jump_table; owner: dungeon/func_80EE7D14. */
const void *const D_8016A870[5] __attribute__((aligned(4))) = {
    ((u8 *)advance_flashing_sprite_sequence + 0x48),
    ((u8 *)advance_flashing_sprite_sequence + 0xD4),
    ((u8 *)advance_flashing_sprite_sequence + 0x118),
    ((u8 *)advance_flashing_sprite_sequence + 0x178),
    ((u8 *)advance_flashing_sprite_sequence + 0x23C)
};
