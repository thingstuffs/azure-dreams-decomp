#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void func_8052DF24(void) __attribute__((noreturn));
extern void func_8052DF60(void) __attribute__((noreturn));

void func_80813294(void *arg0, s32 unused, void *arg2) {
    register u16 ten ASM_REG("$3");
    s32 state;

    state = FIELD(arg0, s16, 4);
    FIELD(arg0, u16, 6) = FIELD(arg0, u16, 6) - 1;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        func_8052DF60();
    }
    if (state == 2) {
        goto state_2;
    }
    func_8052DF60();

state_0:
    if (FIELD(FIELD(arg0, void *, 0), s16, 0x5C) == 4) {
        ten = 10;
        ASM_KEEP(ten);
        (void)FIELD(arg0, volatile u16, 4);
        FIELD(arg0, u16, 6) = ten;
        func_8052DF24();
    }
    return;

state_1:
    FIELD(arg2, u16, 0x16) = FIELD(arg2, u16, 0x16) + 0x40;
    if ((s16)FIELD(arg0, u16, 6) <= 0) {
        FIELD(arg0, u16, 4) = FIELD(arg0, u16, 4) + 1;
        func_8052DF60();
    }
    return;

state_2:
    FIELD(arg2, u16, 0x16) = FIELD(arg2, u16, 0x16) - 0x18;
    if (FIELD(arg2, volatile u16, 0x16) < 0x18U) {
        FIELD(arg2, u16, 0x16) = 0;
        FIELD(arg0, s16, 4) = 0;
    }
}
