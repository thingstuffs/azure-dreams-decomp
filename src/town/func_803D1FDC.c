/* Relink of matched town/func_8032EA2C; every changed retail word is a paired relocation. */
#define townProcessLshopEntries func_80018FDC
#include "common.h"

extern void func_80018BE4(s32);
extern void func_80018C58(void);
extern void func_80018E70(void *);
extern void func_80018F9C(void *);

/* Processes flagged four-byte entries according to the mode, skipping type 0x18. */
void func_80018FDC(void *entries, s32 entry_mode)
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
                    func_80018E70(entry);
                    entry += 4;
                } else {
                    func_80018F9C(entry);
                    func_80018BE4(entry_index);
                    entry += 4;
                }
            } else {
                entry += 4;
            }
            entry_index++;
        } while (entry[1] != 0);
    }
    func_80018C58();
}
