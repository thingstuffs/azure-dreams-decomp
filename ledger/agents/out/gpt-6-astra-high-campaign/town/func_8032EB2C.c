#include "common.h"

extern void *D_80016000;

/* Count entries in the zero-terminated table. */
s32 func_8001932C(void) {
    s32 *entry;
    s32 count;
    void *table;

    do { table = *(void **)((u8 *)D_80016000 + 0x38); } while (0);
    entry = (s32 *)((u8 *)table + 0x29C);
    count = 0;
    if (*(s32 *)((u8 *)table + 0x29C) != 0) {
        do {
            entry++;
            count++;
        } while (*entry != 0);
    }
    return count;
}
