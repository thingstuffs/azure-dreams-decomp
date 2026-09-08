#include "common.h"

/* Checks whether a value appears in the zero-terminated table. */
s32 func_8008B2E4(s32 value) {
    s32 *entry = (s32 *)0x800D0000;

    ASM_KEEP(entry);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    if (entry[-0x1E9] != 0) {
        entry += -0x1E9;
        do {
            if (value == *entry) {
                return 1;
            }
            entry++;
        } while (*entry != 0);
    }
    return 0;
}
