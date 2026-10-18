#include "common.h"

void set_glyph_style_index(void *record, int index);
void func_8004E884(u8 *entries, s32 process_arg);

/* Processes consecutive 12-byte entries starting at the requested index. */
void card_boot_highlight_dialog_text_range(s32 entry_base, s32 start_index, s32 entry_count) {
    s32 entry_index;
    s32 entry_addr;

    func_8004E884(entry_base, 1);
    entry_addr = entry_base + (start_index * 0xC);
    entry_index = 0;
    if (entry_count > 0) {
        do {
            set_glyph_style_index(entry_addr, 0);
            entry_index += 1;
            entry_addr += 0xC;
        } while (entry_index < entry_count);
    }
}
