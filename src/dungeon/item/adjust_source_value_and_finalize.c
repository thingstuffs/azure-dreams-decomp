#include "dungeon/item/message.h"

extern s32 display_text_with_fullwidth_adjustment(s8 *text);

/* Prefix the supplied message with the entity text and display the buffer. */
void adjust_source_value_and_finalize(void *context, const void *source)
{
    const u8 *source_copy;
    void *original_value;
    void *current_value;
    void *adjusted_value;
    adjusted_value = append_entity_display_text(context, current_value = get_unused_text_buffer());
    original_value = current_value;
    current_value = adjusted_value;
    clear_byte_and_advance(expand_text_control_codes(source_copy = source, current_value));
    display_text_with_fullwidth_adjustment(original_value);
}
