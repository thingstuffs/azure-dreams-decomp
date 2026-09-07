#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_800A5BC4(void) __attribute__((noreturn));
extern void func_800A5C68(void) __attribute__((noreturn));
extern s32 D_800814A0[3];
extern s32 D_80083170[3];

void func_800A5AF0(void *arg0, void *arg1, void *arg2) {
    s16 divisor;
    s16 timer;
    s16 state;
    u16 value;

    state = FIELD(arg0, s16, 4);
    if (state == 0) {
        FIELD(arg1, s16, 2) = (s16)(
            (u16)FIELD(arg1, s16, 2) +
            ((s32)(FIELD(arg0, s16, 8) - FIELD(arg1, s16, 2)) /
             (s16)FIELD(arg0, s16, 6)));

        value = FIELD(arg2, u16, 0x1C);
        divisor = FIELD(arg0, s16, 6);
        FIELD(arg2, u16, 0x1C) =
            (u16)(value + ((s32)(0x1000 - value) / divisor));

        timer = (u16)FIELD(arg0, s16, 6) - 1;
        FIELD(arg0, s16, 6) = timer;
        if ((timer << 16) <= 0) {
            u16 next_state;

            FIELD(arg0, s16, 6) = 0x30;
            FIELD(arg2, u16, 0x1C) = 0x1000;
            next_state = FIELD(arg0, u16, 4) + 1;
            ASM_TAILSLOT_PIN(next_state);
            func_800A5BC4();
        }
    } else if (state == 1) {
        if (D_80083170[0] != 0) {
            FIELD(arg0, s16, 6) = 0;
        }

        timer = (u16)FIELD(arg0, s16, 6) - 1;
        FIELD(arg0, s16, 6) = timer;
        if ((timer << 16) <= 0) {
            u16 next_state = FIELD(arg0, u16, 4);

            FIELD(arg0, s16, 6) = 0x20;
            FIELD(arg0, u16, 4) = next_state + 1;
            func_800A5C68();
        }
    } else {
        FIELD(arg2, u8, 0xE) = (u8)(
            FIELD(arg2, u8, 0xE) -
            ((s32)FIELD(arg2, u8, 0xE) / (s16)FIELD(arg0, s16, 6)));
        FIELD(arg2, u8, 0xD) = (u8)(
            FIELD(arg2, u8, 0xD) -
            ((s32)FIELD(arg2, u8, 0xD) / (s16)FIELD(arg0, s16, 6)));
        FIELD(arg2, u8, 0xC) = (u8)(
            FIELD(arg2, u8, 0xC) -
            ((s32)FIELD(arg2, u8, 0xC) / (s16)FIELD(arg0, s16, 6)));

        timer = (u16)FIELD(arg0, s16, 6) - 1;
        FIELD(arg0, s16, 6) = timer;
        if ((timer << 16) <= 0) {
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
    }
}

/* MECHANISM: Both callees are zero-argument noreturn continuations, allowing LEAD 19
   to erase the false RA-only frame. The first tail holds state+1 in $v0, and
   ASM_TAILSLOT_PIN sinks its addiu into the tail-j delay slot; the second is natural. */
