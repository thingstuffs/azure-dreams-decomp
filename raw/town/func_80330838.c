#include "common.h"

extern void *D_80016000;

s32 func_8001B038(s32 arg0) {
    s32 result;
    s32 i;
    void *entry;

    entry = (void *)(*(s32 *)((s8 *)D_80016000 + 0x38) + 0x33A4);
    do { i = 0; } while (0);
loop:
    if (*(u8 *)((s8 *)entry + 1) == arg0) {
        result = 1;
        goto done;
    }
    i++;
    entry += 2;
    if (i < 0x22) {
        goto loop;
    }
    result = 0;
done:
    return result;
}
