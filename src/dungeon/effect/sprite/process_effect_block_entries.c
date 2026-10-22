#include "common.h"
#include "dungeon/effect/sprite.h"

extern void advance_sprite_animation_and_textures(void *entry);

extern struct {
    s32 value;
    s32 pad[2];
} D_800814A0;

/* Propagate the high flag bit and process each entry in the block. */
void process_effect_block_entries(void *block) {
    s32 entry_index;

    if (*(*(u16 **)((u8 *)block + 0x98)) & 0x8000) {
        *((u16 *)block - 1) |= 0x8000;
        D_800814A0.value |= 0x8000;
    }

    for (entry_index = 0; entry_index < *(s16 *)((u8 *)block + 2); entry_index++) {
        advance_sprite_animation_and_textures((u8 *)block + 8 + entry_index * 0x30);
    }
}
