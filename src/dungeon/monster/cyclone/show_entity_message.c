#include "common.h"
#include "shared/entity.h"
#include "dungeon/item.h"
#include "dungeon/item/message.h"
#include "dungeon/monster/cyclone.h"
#include "dungeon/system.h"

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
