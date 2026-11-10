#include "frontend/libcard/paired_choice.h"
#include "common.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "slus.h"




extern FrameNode card_choice_cursor_data;


/* Place the left and right choice items and start each one's cursor stream on its payload word. */
void position_paired_choice_items(CardChoiceOwner *state) {
    CardChoiceDisplayNode *left_item;
    CardChoiceDisplayNode *right_item;

    left_item = state->pointers[2];
    left_item->block->fields.x = 0x40;
    left_item->block->fields.y = 0x20;
    initialize_scaled_entry_cursor(&state->choice_cursors[0], &card_choice_cursor_data, &left_item->payload.word);
    right_item = state->pointers[3];
    right_item->block->fields.x = 0xC0;
    right_item->block->fields.y = 0x20;
    initialize_scaled_entry_cursor(&state->choice_cursors[1], &card_choice_cursor_data, &right_item->payload.word);
}
