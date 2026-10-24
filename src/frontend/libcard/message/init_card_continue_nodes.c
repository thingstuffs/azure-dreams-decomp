#include "frontend/libcard/message.h"

/* The Continue owner supplies 18 linked display slots at these offsets. */
typedef struct CardContinueNodes {
    /* 0x000 */ u8 pad_000[0x184];
    /* 0x184 */ DisplayPositionWords vector;
    /* 0x190 */ u8 pad_190[0x10];
    /* 0x1A0 */ CardDisplayNode *pointers[18];
    /* 0x1E8 */ CardDisplayNode nodes[18];
    /* 0x308 */ CardDisplayBlock blocks[18];
} CardContinueNodes;

/* Sibling message files declare these templates through their own local views. */
extern CardDisplayBlock display_block_defaults;
extern DisplayPositionWords display_vector_defaults;

/* Build the requested node links and copy their common display defaults. */
void init_card_continue_nodes(CardContinueNodes *owner, s32 count)
{
    s32 i;
    s32 word0;
    s32 word1;
    s32 word2;
    s32 word3;

    for (i = 0; i < count; i++) {
        word0 = display_block_defaults.words[0];
        owner->pointers[i] = &owner->nodes[i];
        owner->blocks[i].words[0] = word0;
        word1 = display_block_defaults.words[1];
        owner->blocks[i].words[1] = word1;
        word2 = display_block_defaults.words[2];
        owner->blocks[i].words[2] = word2;
        word3 = display_block_defaults.words[3];
        owner->nodes[i].block = &owner->blocks[i];
        owner->nodes[i].vector = &owner->vector;
        owner->blocks[i].words[3] = word3;
    }
    owner->vector.unk0 = display_vector_defaults.unk0;
    owner->vector.unk4 = display_vector_defaults.unk4;
    owner->vector.unk8 = display_vector_defaults.unk8;
}
