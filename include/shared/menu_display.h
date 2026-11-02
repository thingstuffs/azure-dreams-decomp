#ifndef SHARED_MENU_DISPLAY_H
#define SHARED_MENU_DISPLAY_H

#include "common.h"
#include "shared/gpu_packets.h"

/* Display nodes and blocks shared by engine selection menus and card panels.
 * Keep the existing tags for consumers that forward-declare them. The block
 * is sixteen bytes and the node links it alongside its position-vector data. */
typedef union CardDisplayBlock {
    s32 words[4];
    struct {
        s32 unk_00;
        s32 unk_04;
        s16 x;
        s16 y;
        s16 depth;
        u8 unk_0E;
        u8 mode;
    } fields;
    struct { u8 r, g, b, pad_03; } color;
    struct { u8 pad_00[0xA]; u16 y; } unsigned_position;
} MenuDisplayBlock;

typedef struct CardDisplayNode {
    s32 unk_00;
    MenuDisplayBlock *block;
    DisplayPositionWords *vector;
    s32 unk_0C;
} MenuDisplayNode;

#endif
