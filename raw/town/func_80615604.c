#include "common.h"

extern s32 func_80018CC0(void);
extern s32 D_80019144[];

s32 func_80016E04(void) {
    s32 index = func_80018CC0();
    s32 *base = D_80019144;
    s32 *entry;

    if (index < 0x29) {
        entry = &base[index];
    } else {
        entry = &base[40];
    }
    ASM_USE(base);
    return *entry;
}
