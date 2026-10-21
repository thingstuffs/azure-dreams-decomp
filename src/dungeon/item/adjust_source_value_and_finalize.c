#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern s32 append_entity_display_text(void *record, u8 *out);
extern void display_text_with_fullwidth_adjustment(s8 *text);
/* Adjusts a computed value for application to the source and finalizes the original value. */
void adjust_source_value_and_finalize(s32 context, void *source, s32 first_input, s32 second_input)
{
    void *source_copy;
    s32 original_value;
    s32 current_value;
    s32 adjusted_value;
    adjusted_value = append_entity_display_text(context, current_value = get_unused_text_buffer());
    original_value = current_value;
    current_value = adjusted_value;
    clear_byte_and_advance(expand_text_control_codes(source_copy = source, current_value));
    display_text_with_fullwidth_adjustment(original_value);
}
