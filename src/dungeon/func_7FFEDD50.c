#include "common.h"

extern u8 D_800CF828[15];
extern s32 D_800CF838[];
extern void func_80041284(s32);
extern s32 func_8008B328(void);

void func_8008B4B0(void) {
    s32 i;
    u8 *entry;

    for (i = 0; i < 15; i++) {
        entry = &D_800CF828[i];
        if (*entry != 0) {
            func_80041284(D_800CF838[*entry]);
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
