#include "frontend/libcard/message.h"

/* The defaults are copied as words, then individual display fields change. */
typedef union CardChoiceBlock {
    s32 words[4];
    struct {
        s32 unk_00;
        s32 unk_04;
        s16 unk_08;
        s16 unk_0A;
        s16 unk_0C;
        u8 unk_0E;
        u8 unk_0F;
    } display;
} CardChoiceBlock;

typedef struct CardChoiceVector {
    s32 words[3];
} CardChoiceVector;

typedef struct CardChoiceEntry {
    s32 unk_00;
    CardChoiceBlock *block;
    CardChoiceVector *vector;
} CardChoiceEntry;

extern CardChoiceBlock display_block_defaults;
extern CardChoiceVector display_vector_defaults;

/* Copy the two default templates, link them, and set the choice-panel display fields. */
void init_card_choice_templates(void *entry_data, void *block_data, void *vector_data)
{
    CardChoiceEntry *entry = entry_data;
    CardChoiceBlock *block = block_data;
    CardChoiceVector *vector = vector_data;
    CardChoiceBlock *block_template = &display_block_defaults;
    CardChoiceVector *vector_template = &display_vector_defaults;
    s32 *vector_head;

    block->words[0] = block_template->words[0];
    vector_head = &vector_template->words[0];
    block->words[1] = block_template->words[1];
    block->words[2] = block_template->words[2];
    block->words[3] = block_template->words[3];
    vector->words[0] = *vector_head;
    vector->words[1] = vector_template->words[1];
    vector->words[2] = vector_template->words[2];
    entry->block = block;
    entry->vector = vector;
    entry->unk_00 = 0;
    entry->block->display.unk_08 = -160;
    entry->block->display.unk_0A = -120;
    entry->block->display.unk_0C = 512;
    entry->block->display.unk_0F = 4;
}
