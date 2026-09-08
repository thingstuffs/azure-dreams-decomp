#include "common.h"

extern u8 D_800CF828[15];
extern s32 D_800CF838[];
extern void func_80041284(s32);
extern s32 func_8008B328(void);

/* Processes nonzero table entries and updates the first slots from the status check. */
void func_8008B4B0(void) {
    s32 slot;
    u8 *entry_id;

    for (slot = 0; slot < 15; slot++) {
        entry_id = &D_800CF828[slot];
        if (*entry_id != 0) {
            func_80041284(D_800CF838[*entry_id]);
        }
    }
    if (func_8008B328() == 0)
        goto clear;
    D_800CF828[0] = 1;
    D_800CF828[1] = 0;
    goto done;
clear:
    D_800CF828[0] = 0;
done:
    return;
}
