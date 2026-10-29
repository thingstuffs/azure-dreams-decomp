#include "dungeon/item/message.h"
#include "dungeon/system.h"

/* Expand the supplied text into a free buffer and display the result. */
void display_formatted_context_message(void *context) {
    void *computed_value;
    void *cursor;

    computed_value = get_unused_text_buffer();
    cursor = expand_text_control_codes(context, computed_value);
    clear_byte_and_advance(cursor);
    display_text_with_fullwidth_adjustment(computed_value);
}
