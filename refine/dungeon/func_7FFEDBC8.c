#include "common.h"

extern s32 func_8008B2E4(s32 arg0);

extern u8 D_800CF828[15];
extern s32 D_800CF838[16];

/* Return whether any of the 15 indexed table entries passes func_8008B2E4. */
s32 func_8008B328(void) {
    s32 slot;
    u8 *entry_indices;
    s32 *entries;
    s32 any_found;

    slot = 0;
    entry_indices = D_800CF828;
    entries = D_800CF838;
loop_1:
    {
        s32 found = func_8008B2E4(entries[*(u8 *)((u32)slot + (u32)entry_indices)]);

        ASM_KEEP(found);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        slot += 1;
        if (found != 0) {
            any_found = 1;
            goto epilogue;
        }
    }
    if (slot < 0xF) {
        goto loop_1;
    }
    any_found = 0;
epilogue:
    return any_found;
}
