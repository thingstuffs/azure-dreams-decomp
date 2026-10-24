#include "frontend/libcard/message.h"

typedef struct CardChoiceBlock {
    s32 words[4];
} CardChoiceBlock;

typedef struct CardChoiceVector {
    s32 words[3];
} CardChoiceVector;

typedef struct CardChoiceNode {
    s32 unk_00;
    CardChoiceBlock *block;
    CardChoiceVector *vector;
    s32 unk_0C;
} CardChoiceNode;

/* create_visual_object clears a 0xF0-byte body and requests four nodes. */
typedef struct CardChoiceOwner {
    u8 pad_00[0x44];
    CardChoiceVector vector;
    u8 pad_50[0x10];
    CardChoiceNode *pointers[4];
    CardChoiceNode nodes[4];
    CardChoiceBlock blocks[4];
} CardChoiceOwner;

extern CardChoiceBlock display_block_defaults;
extern CardChoiceVector display_vector_defaults;

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
    owner->vector.words[0] = display_vector_defaults.words[0];
    owner->vector.words[1] = display_vector_defaults.words[1];
    owner->vector.words[2] = display_vector_defaults.words[2];
}
