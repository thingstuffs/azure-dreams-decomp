#include "common.h"

extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes();
extern s32 clear_byte_and_advance();
extern s32 append_entity_display_text();
extern s32 display_text_with_fullwidth_adjustment();
extern s8 D_8017646B[9];

/*
 * Appends the entity name and expanded D_8017646B message to an unused text buffer, terminates it,
 * and displays it with fullwidth adjustment.
 */
void build_and_display_encoded_message(s32 source_value, s32 input_value, s32 input_value_2, s32 input_value_3) {
    s32 original_value;
    s32 current_value;
    s32 adjusted_value;

    adjusted_value = append_entity_display_text(source_value, current_value = get_unused_text_buffer());
    original_value = current_value;
    current_value = adjusted_value;
    clear_byte_and_advance(expand_text_control_codes(D_8017646B, current_value));
    display_text_with_fullwidth_adjustment(original_value);
}
