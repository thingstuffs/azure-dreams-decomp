#include "common.h"

extern s32 func_80401E2C(s32 arg0);
extern s32 func_80404364(void *arg0, s32 arg1);
extern void func_8040325C(void *arg0);
extern void func_80406648(void) __attribute__((noreturn));
extern void func_80406590(void);
extern void func_80405A3C(void);

void func_8001F5CC(void *arg0) {
    void *base;
    s32 idx;

    base = arg0;
    idx = *(s32 *)((u8 *)base + 0x24);
    if (idx < 5) {
        if (func_80401E2C(idx) != 0) {
            *(s32 *)((u8 *)base + 4 + idx * 4) = func_80404364((u8 *)base - 0x20, idx);
            *(s32 *)((u8 *)base + 0x24) = *(s32 *)((u8 *)base + 0x24) + 1;
            return func_80406648();
        }
        *(void (**)(void))((u8 *)base + 0x34) = func_80406590;
        func_8040325C((u8 *)base - 0x20);
        *(void (**)(void))((u8 *)base - 0x10) = func_80405A3C;
    }
    if (idx == 5) {
        *(void (**)(void))((u8 *)base - 0x10) = func_80406590;
    }
}
