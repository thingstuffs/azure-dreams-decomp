#include "common.h"
#include "shared/entity.h"

extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(const u8 *src, u8 *dst);
extern void * clear_byte_and_advance(s8 *byte_ptr);
extern u8 *append_entity_display_text(void *record, u8 *out);
extern s32 display_text_with_fullwidth_adjustment(s8 *text);
extern s8 D_8017646B[9];

/*
 * Appends the entity name and expanded D_8017646B message to an unused text buffer, terminates it,
 * and displays it with fullwidth adjustment.
 */
void build_and_display_encoded_message(ActorRecord *body) {
    void *original_value;
    void *current_value;
    void *adjusted_value;

    adjusted_value = append_entity_display_text(body, current_value = get_unused_text_buffer());
    original_value = current_value;
    current_value = adjusted_value;
    clear_byte_and_advance(expand_text_control_codes(D_8017646B, current_value));
    display_text_with_fullwidth_adjustment(original_value);
}
