#ifndef FRONTEND_LIBCARD_PAIRED_CHOICE_H
#define FRONTEND_LIBCARD_PAIRED_CHOICE_H
#include "frontend/libcard/message.h"
/* Choice nodes have the shared 16-byte display layout. The payload is
 * installed as a data pointer and cleared as a full word by animation. */
typedef struct CardChoiceDisplayNode {
    union { void *data; s32 word; } payload;
    MenuDisplayBlock *block;
    DisplayPositionWords *vector;
    s32 unk_0C;
} CardChoiceDisplayNode;

/* create_visual_object clears 0xF0 bytes and initializes four display nodes. */
typedef struct CardChoiceOwner {
    s32 initial_value;
    u8 pad_04[0x20];
    s32 selection;
    MenuDisplayBlock display_block;
    DisplayPositionWords display_vector;
    DisplayPositionWords vector;
    CardDisplayNode display;
    CardChoiceDisplayNode *pointers[4];
    CardChoiceDisplayNode nodes[4];
    CardDisplayBlock blocks[4];
} CardChoiceOwner;
#endif
