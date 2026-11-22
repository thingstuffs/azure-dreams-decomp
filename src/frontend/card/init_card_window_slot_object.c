#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "frontend/card/slot_marker.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "frontend/libcard.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/server_menu.h"

/* Create or reset a slot record, initialize its body, install its callback and return it. */
CardDevSlotWindow *init_card_window_slot_object(ObjectNodeHeader *owner, s32 slot_index)
{
    CardDevSlotWindow *record;
    CardDevMenu10 *body;
    s32 record_offset;

    record_offset = slot_index * 0x360;
    record = (CardDevSlotWindow *)(D_8040A0F0 + record_offset);
    body = &record->body;

    if (slot_index >= 5) {
        printf_8007C040(card_window_slot_assert_format, card_window_slot_assert_filename, 0x12B);
        exit_8007BEF0(1);
    }
    if (slot_index < 0) {
        printf_8007C040(card_window_slot_assert_format, card_window_slot_assert_filename, 0x12C);
        exit_8007BEF0(1);
    }

    if (func_80047FD8(record) == 0) {
        record = func_8003C714(0, record, 0xD8);
        if (record == 0) {
            printf_8007C040(card_window_slot_assert_format, card_window_slot_assert_filename, 0x12F);
            exit_8007BEF0(1);
        }
        func_80040560(record, card_dev_render_panel_hierarchy);
    } else {
        card_dev_refresh_slot_window(record);
        record->node.flags &= 0x7FFF;
        bzero_8007BFE0(body, 0x340);
    }

    card_dev_init_slot_window_menu_entries(body, 10);
    record->node.sprite = (SpriteFrameState *)&body->frame;
    body->frame.unk_0C = card_background_bind_template(body->entries);
    func_80404314(body, owner, slot_index);
    record->node.update_callback = card_dev_clear_object_state;
    return record;
}
