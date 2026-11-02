#include "frontend/libcard/paired_choice.h"
#include "common.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "slus.h"




struct S8004CBFC_a0;
struct S8004CBFC_a1;
struct S8004CBFC_a1; extern struct S8004CBFC_a1 card_choice_cursor_data;


/* Position and initialize the left and right items. */
void set_entry_destination_and_value(void *state_arg) {
    CardChoiceOwner *state = state_arg;
    CardChoiceDisplayNode *left_item;
    CardChoiceDisplayNode *right_item;

    left_item = state->pointers[2];
    left_item->block->fields.x = 0x40;
    left_item->block->fields.y = 0x20;
    initialize_scaled_entry_cursor(state_arg + 4, &card_choice_cursor_data, left_item);
    right_item = state->pointers[3];
    right_item->block->fields.x = 0xC0;
    right_item->block->fields.y = 0x20;
    initialize_scaled_entry_cursor(state_arg + 0x10, &card_choice_cursor_data, right_item);
}
