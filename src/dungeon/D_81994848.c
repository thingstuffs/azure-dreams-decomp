#include "common.h"

extern void update_palette_particle_transition(void *, void *, void *);

/* jump_table; owner: dungeon/func_81994D8C. */
const void *const D_80024048[5] __attribute__((aligned(4))) = {
    ((u8 *)update_palette_particle_transition + 0x64),
    ((u8 *)update_palette_particle_transition + 0xE8),
    ((u8 *)update_palette_particle_transition + 0x200),
    ((u8 *)update_palette_particle_transition + 0x80C),
    ((u8 *)update_palette_particle_transition + 0xBA0)
};
