#include "common.h"
#include "m2c_compat.h"

s32 func_80026F54();
s32 func_80026FA8();
void *func_80027110();
s32 func_8004B404();
M2C_UNK func_80069E88();

/* Builds a page of fixed-width text entries, with five special entries on the first page. */
s32 func_8002714C(s32 context, s32 scroll_y, s32 entry_count, M2C_UNK list_type) {
    s32 slot;
    s32 dest;
    s32 entry_type;
    s32 text_table;
    s32 buffer;

    entry_type = list_type;
    scroll_y /= 72;
    buffer = func_8004B404(0x91);
    if (buffer != 0) {
        entry_count -= scroll_y * 8;
        if (entry_count >= 9) {
            entry_count = 8;
        }
        if (scroll_y == 0) {
            slot = 0;
            dest = slot;
            scroll_y = buffer;
            do {
                func_80069E88(scroll_y, func_80027110(entry_type, slot | dest), 0x12);
                slot += 1;
                scroll_y += 0x12;
            } while (slot < 5);
            scroll_y = func_80026F54(context, entry_type, 0);
            if (slot < entry_count) {
                text_table = (s32)0x800157C0;
                dest = (slot * 0x12) + buffer;
                do {
                    func_80069E88(dest, (scroll_y * 0x13) + text_table, 0x12);
                    scroll_y = func_80026FA8(context, entry_type, scroll_y + 1);
                    slot += 1;
                    dest += 0x12;
                } while (slot < entry_count);
                return buffer;
            }
        } else {
            scroll_y = func_80026F54(context, entry_type, (scroll_y * 8) - 5);
            slot = 0;
            if (entry_count > 0) {
                text_table = (s32)0x800157C0;
                dest = buffer;
                do {
                    func_80069E88(dest, (scroll_y * 0x13) + text_table, 0x12);
                    scroll_y = func_80026FA8(context, entry_type, scroll_y + 1);
                    slot += 1;
                    dest += 0x12;
                } while (slot < entry_count);
            }
        }
    }
    return buffer;
}
