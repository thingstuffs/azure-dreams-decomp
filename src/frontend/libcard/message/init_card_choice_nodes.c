#include "frontend/libcard/message.h"

/* create_visual_object clears a 0xF0-byte body and requests four nodes. */
typedef struct CardChoiceOwner {
    /* 0x00 */ u8 pad_00[0x44];
    /* 0x44 */ DisplayPositionWords vector;
    /* 0x50 */ u8 pad_50[0x10];
    /* 0x60 */ CardDisplayNode *pointers[4];
    /* 0x70 */ CardDisplayNode nodes[4];
    /* 0xB0 */ CardDisplayBlock blocks[4];
} CardChoiceOwner;

/* Sibling message files declare these templates through their own local views. */
extern CardDisplayBlock display_block_defaults;
extern DisplayPositionWords display_vector_defaults;

/* Build the requested node links and copy their common display defaults. */
void init_card_choice_nodes(CardChoiceOwner *owner, s32 count)
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
