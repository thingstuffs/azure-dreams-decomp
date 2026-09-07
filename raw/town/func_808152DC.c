#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_80058F88();
extern void func_8052FF70(void) __attribute__((noreturn));
extern s32 D_80084D5C;

void func_808152DC(void *arg0) {
    s16 state;
    u16 timer;

    state = FIELD(arg0, s16, 0x50);
    if (state != 0) {
        if (state != 1) {
            func_8052FF70();
            return;
        }
        goto active;
    }

    func_80058F88(0x603);
    FIELD(arg0, s16, 0x50) = (u16)((u16)FIELD(arg0, s16, 0x50) + 1);

active:
    timer = FIELD(arg0, u16, 0x52) - 1;
    FIELD(arg0, u16, 0x52) = timer;
    if ((timer << 0x10) <= 0) {
        func_80058F88(0x1603);
        FIELD(arg0, u16, -2) = FIELD(arg0, u16, -2) | 0x8000;
        D_80084D5C |= 0x8000;
    }
}
