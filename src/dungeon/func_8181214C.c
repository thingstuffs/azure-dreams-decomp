#include "common.h"
#include "m2c_compat.h"

s32 func_80026F54();
s32 func_80026FA8();
void *func_80027110();
s32 func_8004B404();
M2C_UNK func_80069E88();
extern M2C_UNK D_800157C0;

/* Builds a page of fixed-width text entries, with five special entries on the first page. */
s32 func_8002714C(s32 context, s32 scroll_y, s32 entry_count, M2C_UNK list_type) {
    s32 cursor;
    s32 slot;
    s32 dest;
    s32 page_count;
    s32 entry_type;
    s32 text_table;
    s32 buffer;

    cursor = scroll_y;
    page_count = entry_count;
    entry_type = list_type;
    cursor /= 72;
    ASM_USE_NV(entry_type);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    buffer = func_8004B404(0x91);
    if (buffer != 0) {
        page_count -= cursor * 8;
        if (page_count >= 9) {
            page_count = 8;
        }
        if (cursor == 0) {
            slot = 0;
            ASM_KEEP_NV(slot);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            dest = slot;
            cursor = buffer;
            do {
                func_80069E88(cursor, func_80027110(entry_type, slot | dest), 0x12);
                slot += 1;
                cursor += 0x12;
            } while (slot < 5);
            cursor = func_80026F54(context, entry_type, 0);
            if (slot < page_count) {
                text_table = (s32)0x800157C0;
                dest = (slot * 0x12) + buffer;
                do {
                    func_80069E88(dest, (cursor * 0x13) + text_table, 0x12);
                    cursor = func_80026FA8(context, entry_type, cursor + 1);
                    slot += 1;
                    dest += 0x12;
                } while (slot < page_count);
                return buffer;
            }
        } else {
            cursor = func_80026F54(context, entry_type, (cursor * 8) - 5);
            slot = 0;
            if (page_count > 0) {
                text_table = (s32)0x800157C0;
                dest = buffer;
                do {
                    func_80069E88(dest, (cursor * 0x13) + text_table, 0x12);
                    cursor = func_80026FA8(context, entry_type, cursor + 1);
                    slot += 1;
                    dest += 0x12;
                } while (slot < page_count);
            }
        }
    }
    return buffer;
}
