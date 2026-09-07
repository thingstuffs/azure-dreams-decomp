#include "common.h"

extern s16 D_80017614;

extern void func_80017380(s32);
extern void func_800173F8(s32);
extern void func_80016210(void) __attribute__((noreturn));

void func_8050E1B0(void)
{
    s16 temp;

    temp = D_80017614 + 1;
    D_80017614 = temp;
    if (temp >= 0x15) {
        D_80017614 = 9;
    }
    if ((D_80017614 == 8) || (D_80017614 == 0x14)) {
        func_80017380(0xAE6);
        func_80016210();
        return;
    }
    func_800173F8(0xAE6);
}
