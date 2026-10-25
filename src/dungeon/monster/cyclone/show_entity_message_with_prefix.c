#include "common.h"

extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(u8 *src, u8 *dst);
extern void *clear_byte_and_advance(s8 *byte_ptr);
extern u8 *append_entity_display_text(void *record, u8 *out);
extern void display_text_with_fullwidth_adjustment(s8 *text);

extern u8 D_800E1F7B[];
extern u8 D_800E1F93[];
extern u8 D_8017088C[];

/* Processes the input, then dispatches or finalizes the result according to the mode. */
void show_entity_message_with_prefix(s32 dispatch_mode, void *input) {
    void *result;

    result = get_unused_text_buffer();
    if (dispatch_mode << 16) {
        clear_byte_and_advance(expand_text_control_codes(D_800E1F7B, append_entity_display_text(input, result)));
    } else {
        clear_byte_and_advance(expand_text_control_codes(D_8017088C,
            append_entity_display_text(input, expand_text_control_codes(D_800E1F93, result))));
    }
    display_text_with_fullwidth_adjustment(result);
}
