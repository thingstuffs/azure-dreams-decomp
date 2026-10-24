#include "frontend/libcard/message.h"

/* Sibling message files declare these templates through their own local views. */
extern CardDisplayBlock display_block_defaults;
extern DisplayPositionWords display_vector_defaults;

/* Copy the display templates and place the Continue panel at (-152, -98). */
void init_card_continue_templates(CardDisplayNode *entry, CardDisplayBlock *block, DisplayPositionWords *vector)
{
    CardDisplayBlock *block_template = &display_block_defaults;
    DisplayPositionWords *vector_template = &display_vector_defaults;
    s32 *vector_head;

    block->words[0] = block_template->words[0];
    vector_head = &vector_template->unk0;
    block->words[1] = block_template->words[1];
    block->words[2] = block_template->words[2];
    block->words[3] = block_template->words[3];
    vector->unk0 = *vector_head;
    vector->unk4 = vector_template->unk4;
    vector->unk8 = vector_template->unk8;
    entry->block = block;
    entry->vector = vector;
    entry->unk_00 = 0;
    entry->block->fields.x = -152;
    entry->block->fields.y = -98;
    entry->block->fields.depth = 512;
    entry->block->fields.mode = 4;
}
