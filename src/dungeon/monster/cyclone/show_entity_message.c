#include "common.h"
#include "shared/entity.h"

extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern u8 *append_entity_display_text(void *record, u8 *out);
extern void display_text_with_fullwidth_adjustment(s8 *text);

extern u8 D_800E1F65[9];
extern u8 D_800E1FB9[9];

/* Format an entity message or dispatch its alternate message. */
void show_entity_message(s32 alternate_message, ActorRecord *entity)
{
    void *text_ctx;

    text_ctx = get_unused_text_buffer();
    if (alternate_message << 16) {
        clear_byte_and_advance(expand_text_control_codes(D_800E1FB9,
                                    append_entity_display_text(entity, text_ctx)));
        display_text_with_fullwidth_adjustment(text_ctx);
        return;
    }
    clear_byte_and_advance(expand_text_control_codes(D_800E1F65,
                                append_entity_display_text(entity, text_ctx)));
    display_text_with_fullwidth_adjustment(text_ctx);
}
