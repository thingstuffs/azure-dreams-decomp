#include "frontend/libcard/paired_choice.h"
#include "common.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "slus.h"




struct S8004CBFC_a0;
struct S8004CBFC_a1;
struct S8004CBFC_a1; extern struct S8004CBFC_a1 card_choice_cursor_data;


/* Position and initialize the left and right items. */
void set_entry_destination_and_value(CardChoiceOwner *state_arg) {
    CardChoiceOwner *state = state_arg;
    CardChoiceDisplayNode *left_item;
    CardChoiceDisplayNode *right_item;
    void *left_cursor_state;
    void *right_cursor_state;

    left_item = state->pointers[2];
    left_item->block->fields.x = 0x40;
    left_item->block->fields.y = 0x20;
    left_cursor_state = &state->choice_cursors[0];
    initialize_scaled_entry_cursor(left_cursor_state, &card_choice_cursor_data, left_item);
    right_item = state->pointers[3];
    right_item->block->fields.x = 0xC0;
    right_item->block->fields.y = 0x20;
    right_cursor_state = &state->choice_cursors[1];
    initialize_scaled_entry_cursor(right_cursor_state, &card_choice_cursor_data, right_item);
}
