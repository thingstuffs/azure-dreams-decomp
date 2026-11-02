#ifndef FRONTEND_LIBCARD_SLOT_LIST_H
#define FRONTEND_LIBCARD_SLOT_LIST_H
#include "shared/menu_display.h"
/* The slot-list owner supplies 10 linked display slots at these offsets. */
typedef struct CardSlotListNodes {
    /* 0x000 */ u8 pad_000[0x240];
    /* 0x240 */ DisplayPositionWords vector;
    /* 0x24C */ u8 display_data[0xC];
    /* 0x258 */ s32 chain_word;
    /* 0x25C */ MenuDisplayNode *pointers[10];
    /* 0x284 */ MenuDisplayNode nodes[10];
    /* 0x324 */ MenuDisplayBlock blocks[10];
} CardSlotListNodes;
#endif
