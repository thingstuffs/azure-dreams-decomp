#include "common.h"

extern void release_lshop_entry(s32);
extern void compact_lshop_entry_list(void);
extern void append_town_item(void *);
extern void set_lshop_special_flag(void *);

/* Processes flagged four-byte entries according to the mode, skipping type 0x18. */
void process_lshop_entries(void *entries, s32 entry_mode)
{
    void *entry_list;
    s32 initial_mode;
    u8 *entry;
    s32 entry_index;
    s32 mode;

    entry_list = entries;
    initial_mode = entry_mode;
    entry = entry_list;
    mode = initial_mode;
    entry_index = 0;
    if (entry[1] != 0) {
        entry_list = 0x18;
        do {
            if ((entry[3] & 0x20) && entry[1] != entry_list) {
                if (mode == 0) {
                    append_town_item(entry);
                    entry += 4;
                } else {
                    set_lshop_special_flag(entry);
                    release_lshop_entry(entry_index);
                    entry += 4;
                }
            } else {
                entry += 4;
            }
            entry_index++;
        } while (entry[1] != 0);
    }
    compact_lshop_entry_list();
}
