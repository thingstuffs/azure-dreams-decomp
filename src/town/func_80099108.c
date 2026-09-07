#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
} Unk99108;

extern s32 D_80097D2C[3];
extern s32 D_800D04A4[];
extern s32 D_800D04B8[];

extern void func_80096908(void) __attribute__((noreturn));
extern void func_80096918(Unk99108 *, s32, s32, s32 *);
extern void func_80096924(Unk99108 *, s32, s32, s32 *);

void func_80096868(Unk99108 *arg0, s32 arg1, s32 arg2, s32 *arg3)
{
    s32 *outer;
    s32 value;

    outer = D_800D04A4;
    if (*outer != 0) {
        do {
            value = arg0->unk0;
            if (value == *outer) {
                if (value == (s32)D_80097D2C) {
                    arg3 = D_800D04B8;
                    if (*arg3 != 0) {
                        do {
                            if (arg0->unk4 != *arg3++) {
                                continue;
                            }
found:
                            func_80096924(arg0, arg1, arg2, arg3);
                            func_80096908();
                            return;
                        } while (*arg3 != 0);
                    }
                } else {
                    goto found;
                }
            }
            outer++;
        } while (*outer != 0);
    }
    func_80096918(arg0, arg1, arg2, arg3);
}

/* MECHANISM: 0x18 frame saves only ra; the outer sentinel base stays in t0 after a direct first load.
   D_800D04B8 holds its page in t1 and completes arg3 in the guard delay slot.
   The shared found label merges the outer non-special edge with the inner equality fallthrough. */
