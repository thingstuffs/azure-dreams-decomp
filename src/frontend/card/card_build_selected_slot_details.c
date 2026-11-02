#include "frontend/card/slot_details.h"
#include "sdk/libc.h"
#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"







extern CardSaveSlot card_slot_header_cache[];

/* Build the selected slot's text fields and position its status icons. */
void card_build_selected_slot_details(void *panel_data) {
    CardDevSlotDetails *panel = panel_data;
    s16 text_buf[32];
    s16 number_buf[8];
    s16 time_buf[4];
    s16 icon_x;
    s32 *icon_cursor;
    s32 *inactive_icon;
    s32 icon_index;
    s32 icon_data;
    s32 bit_one;
    s16 icon_y;
    u32 hours;
    u32 mins;
    u32 minute_quotient;
    u32 secs;
    u32 second_quotient;
    void *slot_text;
    void *detail_text;
    void *value_text;
    void *time_text;
    void *count_text;
    void *footer_text;
    CardMenuDisplayNode *widget;
    void *widget_cursor;
    void *footer_buf;
    s32 *icon_table;

    widget = panel->text_nodes[0];
    func_8003830C(panel->selected_slot + 1, text_buf);
    func_8007BF50(text_buf, D_80400660);
    func_8007BF50(text_buf, card_slot_detail_records[panel->selected_slot].halfwords);
    slot_text = panel->text_buffers[0];
    func_80051B50(slot_text, text_buf, 1);
    widget->payload.data = slot_text;
    widget->block->fields.x = 0xA9;
    widget->block->fields.y = 0x110;
    widget = panel->text_nodes[1];
    memcpy(text_buf, D_80400668, 0x2A);
    func_80051B50(panel->text_buffers[1], text_buf, 1);
    widget->payload.data = panel->text_buffers[1];
    widget->block->fields.x = 0xBC;
    widget->block->fields.y = 0x110;
    if (card_slot_header_cache[panel->selected_slot].fields.unk_08 != 0) {
        widget = panel->text_nodes[2];
        func_8007BF80(text_buf, D_80408CF4[0]);
        func_8003830C(card_slot_header_cache[panel->selected_slot].fields.unk_34, number_buf);
        func_8007BF50(text_buf, number_buf);
        func_8007BF50(text_buf, D_804006AC);
        detail_text = panel->text_buffers[2];
        func_80051B50(detail_text, text_buf, 1);
        widget->payload.data = detail_text;
        widget->block->fields.x = 0xBC;
        widget->block->fields.y = 0x140;
    }
    widget = panel->text_nodes[3];
    func_80051804(card_slot_header_cache[panel->selected_slot].fields.unk_24, 0xA, text_buf);
    func_80051900(text_buf);
    value_text = panel->text_buffers[3];
    func_80051520(value_text, text_buf, 1);
    widget->payload.data = value_text;
    widget->block->fields.x = 0x140;
    widget->block->fields.y = 0x110;
    widget = panel->text_nodes[4];
    func_80051898(card_slot_header_cache[panel->selected_slot].fields.play_frames, text_buf);
    hours = card_slot_header_cache[panel->selected_slot].fields.play_frames / 216000;
    func_80051804(hours, 3, text_buf);
    func_8007BF50(text_buf, D_804006BC);
    mins = card_slot_header_cache[panel->selected_slot].fields.play_frames / 3600;
    minute_quotient = mins / 3600;
    func_8005184C(mins - minute_quotient * 3600, 2, time_buf);
    func_8007BF50(text_buf, time_buf);
    func_8007BF50(text_buf, D_804006BC);
    secs = card_slot_header_cache[panel->selected_slot].fields.play_frames / 60;
    second_quotient = secs / 60;
    func_8005184C(secs - second_quotient * 60, 2, time_buf);
    func_8007BF50(text_buf, time_buf);
    func_80051900(text_buf);
    time_text = panel->text_buffers[4];
    func_80051520(time_text, text_buf, 1);
    widget->payload.data = time_text;
    widget->block->fields.x = 0x147;
    widget->block->fields.y = 0x120;
    widget = panel->text_nodes[5];
    func_80051804(card_slot_header_cache[panel->selected_slot].fields.unk_2C, 4, text_buf);
    func_80051900(text_buf);
    count_text = panel->text_buffers[5];
    func_80051520(count_text, text_buf, 1);
    widget->payload.data = count_text;
    widget->block->fields.x = 0xF2;
    widget->block->fields.y = 0x120;
    widget = panel->text_nodes[6];
    memcpy(text_buf, D_804006C0, 3);
    footer_buf = text_buf;
    func_80051900(footer_buf);
    footer_text = panel->text_buffers[6];
    func_80051520(footer_text, footer_buf, 1);
    icon_index = 0;
    bit_one = 1;
    icon_table = D_80408CFC;
    inactive_icon = icon_table + 10;
    icon_y = 0xB0;
    icon_x = 0x38;
    icon_cursor = icon_table;
    widget_cursor = panel;
    widget->payload.data = footer_text;
    widget->block->fields.x = 0x180;
    widget->block->fields.y = 0x130;
    do {
        widget = ((CardDevSlotDetails *)widget_cursor)->icon_nodes[0];
        if ((bit_one << icon_index) & card_slot_header_cache[panel->selected_slot].fields.icon_flags) {
            icon_data = *icon_cursor;
        } else {
            icon_data = *inactive_icon;
        }
        icon_cursor += 1;
        widget_cursor += 4;
        widget->payload.word = icon_data;
        icon_index += 1;
        widget->block->fields.x = icon_x;
        widget->block->fields.y = icon_y;
        icon_x += 0x10;
    } while (icon_index < 0xA);
}
