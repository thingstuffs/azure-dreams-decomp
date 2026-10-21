#include "common.h"
#include "engine/text.h"
#include "slus.h"

/* Process 12-byte entries through the entry whose first byte has bit 0x80 set. */
void set_style_for_tagged_glyph_entries(u8 *entries, s32 process_arg)
{
    u8 *entry = entries;
    s32 entry_process_arg = process_arg;

    if (entry != 0) {
        do {
            set_glyph_style_index(entry, entry_process_arg);
            if (*entry & 0x80) {
                break;
            }
            entry = entry + 0xC;
        } while (1);
    }
}
