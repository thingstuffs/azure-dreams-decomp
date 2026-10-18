#include "modules/dungeon_ovl_1831cd8.h"

s32 build_menu_text_page(s32 context, s32 scroll_y, s32 entry_count, s32 list_type) {
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
                func_80069E88(scroll_y, get_mapped_menu_table_entry(entry_type, slot | dest), 0x12);
                slot += 1;
                scroll_y += 0x12;
            } while (slot < 5);
            scroll_y = find_menu_entry_pair_occurrence(context, entry_type, 0);
            if (slot < entry_count) {
                text_table = (s32)0x800157C0;
                dest = (slot * 0x12) + buffer;
                do {
                    func_80069E88(dest, (scroll_y * 0x13) + text_table, 0x12);
                    scroll_y = find_menu_entry_by_pair_from_index(context, entry_type, scroll_y + 1);
                    slot += 1;
                    dest += 0x12;
                } while (slot < entry_count);
                return buffer;
            }
        } else {
            scroll_y = find_menu_entry_pair_occurrence(context, entry_type, (scroll_y * 8) - 5);
            slot = 0;
            if (entry_count > 0) {
                text_table = (s32)0x800157C0;
                dest = buffer;
                do {
                    func_80069E88(dest, (scroll_y * 0x13) + text_table, 0x12);
                    scroll_y = find_menu_entry_by_pair_from_index(context, entry_type, scroll_y + 1);
                    slot += 1;
                    dest += 0x12;
                } while (slot < entry_count);
            }
        }
    }
    return buffer;
}
