#include "frontend/card/slot_details.h"
#include "common.h"
#include "frontend/card.h"
#include "frontend/card/service.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "sdk/memory.h"

typedef struct Local64 { s32 word; s8 byte; u8 pad[59]; } Local64;
typedef struct Local16 { u8 data[16]; } Local16;

typedef struct { s32 word; s8 byte; } TextConstant;
extern TextConstant card_dev_remaining_saves_lead_message;

/* Builds count-dependent text and sets its display position. */
void build_memory_task_text(CardDevSlotDetails *panel) {
    s32 count;
    Local64 count_text;
    Local16 number_text;
    Local64 *count_text_ptr;
    Local16 *number_text_ptr;
    s32 line_index;
    CardDevMenuEntry *text_entry;
    void *join_dst;
    void *join_src;

    count = get_table_entry_by_flag();
    if (count < 3) {
        func_80051B50(panel->text_buffers[0], D_804006C4, 1);
        join_dst = panel->text_buffers[1];
        join_src = D_804006EC;
    } else {
        memcpy(&count_text, &card_dev_remaining_saves_lead_message, 5);
        number_text_ptr = &number_text;
        func_8003830C(count / 3, number_text_ptr);
        count_text_ptr = &count_text;
        func_8007BF50(count_text_ptr, number_text_ptr);
        func_8007BF50(count_text_ptr, D_8040071C);
        join_dst = panel->text_buffers[0];
        join_src = count_text_ptr;
    }
    func_80051B50(join_dst, join_src, 1);
    line_index = 0;
    while (count < 3 ? line_index < 2 : line_index < 1) {
        text_entry = panel->entries[4 + line_index];
        text_entry->display.payload.data = panel->text_buffers[line_index];
        text_entry->display.block->fields.x = 0xA9;
        text_entry->display.block->fields.y = (s16) ((line_index * 0x10) + 0x110);
        line_index += 1;
    }
}
