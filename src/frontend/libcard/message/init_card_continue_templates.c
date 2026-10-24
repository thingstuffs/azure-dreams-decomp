#include "frontend/libcard/message.h"

typedef union CardContinueBlock {
    s32 words[4];
    struct {
        s32 word0;
        s32 word4;
        s16 x;
        s16 y;
        s16 depth;
        u8 pad_E;
        u8 mode;
    } fields;
} CardContinueBlock;

typedef struct CardContinueVector { s32 words[3]; } CardContinueVector;
typedef struct CardContinueEntry {
    s32 state;
    CardContinueBlock *block;
    CardContinueVector *vector;
} CardContinueEntry;

extern CardContinueBlock display_block_defaults;
extern CardContinueVector display_vector_defaults;

/* Copy the display templates and place the Continue panel at (-152, -98). */
void init_card_continue_templates(CardContinueEntry *entry, CardContinueBlock *block,
                                  CardContinueVector *vector)
{
    CardContinueBlock *primary_template = &display_block_defaults;
    CardContinueVector *secondary_template = &display_vector_defaults;
    s32 *secondary_head;

    block->words[0] = primary_template->words[0];
    secondary_head = &secondary_template->words[0];
    block->words[1] = primary_template->words[1];
    block->words[2] = primary_template->words[2];
    block->words[3] = primary_template->words[3];
    vector->words[0] = *secondary_head;
    vector->words[1] = secondary_template->words[1];
    vector->words[2] = secondary_template->words[2];
    entry->block = block;
    entry->vector = vector;
    entry->state = 0;
    entry->block->fields.x = -152;
    entry->block->fields.y = -98;
    entry->block->fields.depth = 512;
    entry->block->fields.mode = 4;
}
