#include "common.h"

#define FIELD(p, type, off) (*(type *)((s8 *)(p) + (off)))

extern void func_80091000(void);
extern void func_800911B0(void) __attribute__((noreturn));
extern void func_80093D48(void *, void *, s32);
extern void func_80093E98(void *, void *, s32);
extern u8 D_80083160[];

void func_80091114(s32 *arg0, void *arg1, s32 arg2) {
    register s32 saved_arg2 ASM_REG("$19") = arg2;
    s32 previous;
    register u8 *state = D_80083160;

    previous = *arg0;
    func_80091000();

    if (previous == *arg0) {
        if (!(FIELD(state, s32, 8) & 0x20)) {
            func_80093D48(arg0, arg1, saved_arg2);
            func_800911B0();
        }

        if ((FIELD(arg1, s32, 0xC) == 0) &&
            (FIELD(arg1, s32, 0x10) == 0)) {
            func_80093E98(arg0, arg1, saved_arg2);
        }
    }
}
