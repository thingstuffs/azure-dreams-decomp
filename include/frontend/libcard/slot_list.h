#ifndef FRONTEND_LIBCARD_SLOT_LIST_H
#define FRONTEND_LIBCARD_SLOT_LIST_H
#include "shared/menu_display.h"
/* Body of one save-slot window node (card_boot_create_slot_window: node
 * D_80029618 + index * 0x3E4, body cleared as 0x3C4 bytes). The glyph and
 * panel buffers are bounded by the next field; their own extents are not
 * established. */
typedef struct CardSlotWindow {
    /* 0x000 */ s32 slot_index;
    /* 0x004 */ s32 owner;
    /* 0x008 */ u8 title_glyphs[0x9C];     /* saved name, or the empty-slot message */
    /* 0x0A4 */ u8 alternate_glyphs[0x60];
    /* 0x104 */ u8 value_glyphs[0x30];
    /* 0x134 */ u8 wide_panel[0x78];       /* func_80023BE4(..., 0x80, 0x18) */
    /* 0x1AC */ u8 small_panel[0x78];      /* func_80023BE4(..., 0x2A, 0x14) */
    /* 0x224 */ MenuDisplayBlock frame_block;
    /* 0x234 */ DisplayPositionWords frame_vector;
    /* 0x240 */ DisplayPositionWords vector;
    /* 0x24C */ MenuDisplayNode frame;     /* the node header's sprite; unk_0C heads the slot chain */
    /* 0x25C */ MenuDisplayNode *pointers[10];
    /* 0x284 */ MenuDisplayNode nodes[10];
    /* 0x324 */ MenuDisplayBlock blocks[10];
} CardSlotWindow;
#endif
