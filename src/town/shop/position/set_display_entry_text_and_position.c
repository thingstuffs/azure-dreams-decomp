#include "common.h"
#include "engine/util.h"
#include "slus.h"
#include "town/shop/position.h"

/* Replace the entry's text, set its position, and select display mode 2. */
void set_display_entry_text_and_position(ItemMenuPart *entry, s32 text, s32 text_style, s16 x, s32 y) {
    void *old_text;

    old_text = entry->handler;
    if (old_text != 0) {
        flag_optional_object_for_removal(old_text);
        entry->handler = 0;
    }
    entry->position->x = x;
    entry->position->y = (s16) y;
    entry->handler = create_label_glyph_entries(text, text_style);
    entry->position->type = 2;
}
