#include "common.h"

extern void townReleaseLshopEntry(s32);
extern void townCompactLshopEntryList(void);
extern void townAppendShopEntry(void *);
extern void townSetLshopSpecialFlag(void *);

/* Processes flagged four-byte entries according to the mode, skipping type 0x18. */
void townProcessLshopEntries(void *entries, s32 entry_mode)
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
                    townAppendShopEntry(entry);
                    entry += 4;
                } else {
                    townSetLshopSpecialFlag(entry);
                    townReleaseLshopEntry(entry_index);
                    entry += 4;
                }
            } else {
                entry += 4;
            }
            entry_index++;
        } while (entry[1] != 0);
    }
    townCompactLshopEntryList();
}
