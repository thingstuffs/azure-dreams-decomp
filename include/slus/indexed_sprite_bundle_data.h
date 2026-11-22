#ifndef SLUS_INDEXED_SPRITE_BUNDLE_DATA_H
#define SLUS_INDEXED_SPRITE_BUNDLE_DATA_H

#include "engine/texture/sprite_part_list.h"

/* Before relocation the word at +0x1C is the byte offset of the row
 * uploaded into both VRAM cache slots. Relocation updates that same word. */
typedef struct S_80048C3C_1 {
    S_80048B8C parts;
    u8 pad_0C[0x10];
    s32 payload_offset;
    s32 width_blocks;
} S_80048C3C_1;

typedef struct S_80048C3C_0 {
    s32 descriptor;
    S_80048C3C_1 *resource;
} S_80048C3C_0;

/* The resident table stores an eight-byte CD descriptor/resource address pair. */
extern S_80048C3C_0 indexed_sprite_bundle_records[];

#endif
