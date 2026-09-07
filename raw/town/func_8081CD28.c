#include "common.h"

extern void func_80026DB4() __attribute__((noreturn));
extern s32 func_80053DA8();
extern s32 D_800814A0[3];

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

void func_80026D28(void *arg0)
{
    s16 state;
    u16 timer;

    state = FIELD(arg0, s16, 0x50);
    if (state != 0) {
        if (state != 1) {
            return func_80026DB4();
        }
        goto tick;
    }

    func_80053DA8(0x603);
    FIELD(arg0, u16, 0x50) = FIELD(arg0, u16, 0x50) + 1;

tick:
    timer = FIELD(arg0, u16, 0x52) - 1;
    FIELD(arg0, u16, 0x52) = timer;
    if ((timer << 16) <= 0) {
        func_80053DA8(0x1603);
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
