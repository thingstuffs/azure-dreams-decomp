#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern void func_80027068(void) __attribute__((noreturn));
extern s32 D_800814A0;

void func_80026FB0(void *arg0, s32 arg1, void *arg2)
{
    s16 state;
    s32 timer;
    s32 value;

    state = FIELD(arg0, s16, 0x64);
    switch (state) {
    default:
        func_80027068();

    case 0:
        timer = (u16)FIELD(arg0, s16, 0x66) - 1;
        FIELD(arg0, s16, 0x66) = timer;
        if ((timer << 16) <= 0) {
            FIELD(arg0, s16, 0x66) = 0x10;
            FIELD(arg0, u16, 0x64) += 1;
            func_80027068();
        }
        break;

    case 1:
        value = FIELD(arg2, u8, 0xC);
        value = value + ((0x80 - value) / FIELD(arg0, s16, 0x66));
        FIELD(arg2, u8, 0xC) = value;
        FIELD(arg2, u8, 0xE) = value;
        FIELD(arg2, u8, 0xD) = value;
        timer = (u16)FIELD(arg0, s16, 0x66) - 1;
        FIELD(arg0, s16, 0x66) = timer;
        if ((timer << 16) <= 0) {
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        break;

    }
}

/* MECHANISM: The zero-argument noreturn tails keep this function frameless.
   Lexically placing default first emits its jump inline before cases 0 and 1.
   Direct scalar D_800814A0 access preserves retail's %hi/%lo displacement. */
