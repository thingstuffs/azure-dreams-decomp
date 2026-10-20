#include "common.h"
#include "m2c_compat.h"

s32 get_unused_text_buffer(void);                                /* extern */
s32 expand_text_control_codes();                        /* extern */
void *func_80099290();                         /* extern */
s32 display_text_with_fullwidth_adjustment();                         /* extern */

/* Computes a value, applies its context-dependent result, and finalizes the value. */
void display_formatted_context_message(s32 context, s32 first_input, s32 second_input, s32 third_input) {
    s32 computed_value;

    computed_value = get_unused_text_buffer();
    func_80099290(expand_text_control_codes(context, computed_value));
    display_text_with_fullwidth_adjustment(computed_value);
}
