#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "shared/widget_views.h"
#include "engine/menu.h"
#include "shared/menu_display.h"


typedef struct S_800500B4_10 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800500B4_10; /* Low halfword of the third display-vector word. */

typedef struct S_800500B4_18 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_800500B4_18; /* Low halfword of the second display-vector word. */

/* Animate the selection cursor and the positions and brightness of six entries. */
void animate_six_entry_selection_cursor(MenuSelectionWidgets *widgets, MenuSelectionBody *anim) {
    s32 entry_index;
    u8 *highlight_ptr;
    s32 start_index;
    s32 target_index;
    s32 frame;
    u8 old_highlight;
    u8 highlight;
    u8 next_highlight;
    MenuDisplayNode *entry_widget;
    MenuDisplayNode *cursor_widget;
    u8 *highlight_base;
    MenuDisplayNode **entry_base;
    s32 cursor_offset;

    start_index = anim->previous_selection;
    cursor_offset = (s32) ((anim->selected_entry - start_index) * (anim->animation_tick << 4)) / (s32) anim->animation_frames;
    cursor_offset = cursor_offset - 0x28;
    (widgets->cursor->block)->fields.y =
        (s16) ((start_index << 4) + cursor_offset);
    ((widgets->secondary_cursor)->block)->unsigned_position.y =
        (u16) (widgets->cursor->block)->unsigned_position.y;
    cursor_widget = widgets->cursor;
    ((S_800500B4_10 *)(cursor_widget->vector))->unk_08 = (s16) ((cursor_widget->block)->unsigned_position.y - 2);
    target_index = anim->selected_entry;
    /* Slots 1..6 and 10..15 select the two widget groups. */
    entry_base = (MenuDisplayNode **)widgets;
    highlight_base = (u8 *) anim;
    ((S_800500B4_18 *)(widgets->cursor->vector))->unk_04 =
        (s16) (-(target_index << 9) - ((s32) ((target_index - anim->previous_selection) * -(anim->animation_tick
        << 9)) / (s32) anim->animation_frames));
    for (entry_index = 0; entry_index < 6; entry_index++) {
        highlight_ptr = highlight_base + entry_index + 0xA4;
        old_highlight = *highlight_ptr;
        if (entry_index == anim->selected_entry) {
            next_highlight = old_highlight + ((s32) (8 - old_highlight) / (s32) ((anim->animation_frames - anim->animation_tick) + 1));
        } else {
            next_highlight = old_highlight;
            if (next_highlight != 0) {
                next_highlight -= 1;
            }
        }
        *highlight_ptr = next_highlight;
        highlight = highlight_base[entry_index + 0xA4];
        ((entry_base[entry_index + 1])->block)->fields.x =
            (s16) highlight;
        ((entry_base[entry_index + 10])->block)->fields.x =
            (s16) (highlight + 0x1E);
        ((entry_base[entry_index + 10])->block)->color.r =
            (highlight_base[entry_index + 0xA4] * 5) + 0x58;
        ((entry_base[entry_index + 10])->block)->color.g =
            (s8) ((highlight_base[entry_index + 0xA4] * 5) + 0x58);
        ((entry_base[entry_index + 10])->block)->color.b =
            (s8) ((highlight_base[entry_index + 0xA4] * 5) + 0x58);
        ((entry_base[entry_index + 1])->block)->color.r =
            (highlight_base[entry_index + 0xA4] * 5) + 0x58;
        ((entry_base[entry_index + 1])->block)->color.g =
            (s8) ((highlight_base[entry_index + 0xA4] * 5) + 0x58);
        entry_widget = entry_base[entry_index + 1];
        entry_widget->block->color.b = (s8) ((highlight_base[entry_index + 0xA4] * 5)
            + 0x58);
    }
    frame = anim->animation_tick;
    if (frame < anim->animation_frames) {
        anim->animation_tick = (s32) (frame + 1);
    }
}
