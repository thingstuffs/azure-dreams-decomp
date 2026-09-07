#include "common.h"

extern s32 func_80021D54(s32 arg0);
extern s32 func_80023FF0(void *arg0, s32 arg1);
extern void func_80023004(void *arg0);
extern void func_80025C50(void) __attribute__((noreturn));
extern void func_80025B9C(void);
extern void func_80024F7C(void);
extern void func_80025B60(void);

void func_80025BD4(void *arg0) {
    void *base;
    s32 idx;

    base = arg0;
    idx = *(s32 *)((u8 *)base + 0x24);
    if (idx < 5) {
        if (func_80021D54(idx) != 0) {
            *(s32 *)((u8 *)base + 4 + idx * 4) = func_80023FF0((u8 *)base - 0x20, idx);
            *(s32 *)((u8 *)base + 0x24) = *(s32 *)((u8 *)base + 0x24) + 1;
            return func_80025C50();
        }
        *(void (**)(void))((u8 *)base + 0x34) = func_80025B9C;
        func_80023004((u8 *)base - 0x20);
        *(void (**)(void))((u8 *)base - 0x10) = func_80024F7C;
    }
    if (idx == 5) {
        *(void (**)(void))((u8 *)base - 0x10) = func_80025B60;
    }
}
