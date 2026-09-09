#include "common.h"

extern s32 func_8004A618(u8 *);
extern s32 func_8004A638(u8 *);

/* Sum results for flagged entries using the selected mode. */
s32 func_800AD828(u8 *entry, s32 mode) {
    register s32 total;
    register u8 *start ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *entry_tag;

    start = entry;
    total = 0;
    if (entry[1] != 0) {
        entry_tag = start + 1;
        do {
            if (entry_tag[2] & 0x20) {
                if (mode == 0) {
                    total += func_8004A638(entry);
                } else {
                    total += func_8004A618(entry);
                }
            }
            entry_tag += 4;
            entry += 4;
        } while (*entry_tag != 0);
    }
    return total;
}
