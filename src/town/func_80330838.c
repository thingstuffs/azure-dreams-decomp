#include "common.h"

extern void *D_80016000;

/* Return whether any of the 34 entries contains the requested byte value. */
s32 func_8001B038(s32 target_value) {
    s32 result;
    s32 entry_index;
    void *entry;

    entry = (void *)(*(s32 *)((s8 *)D_80016000 + 0x38) + 0x33A4);
    do { entry_index = 0; } while (0);
loop:
    if (*(u8 *)((s8 *)entry + 1) == target_value) {
        result = 1;
        goto done;
    }
    entry_index++;
    entry += 2;
    if (entry_index < 0x22) {
        goto loop;
    }
    result = 0;
done:
    return result;
}
