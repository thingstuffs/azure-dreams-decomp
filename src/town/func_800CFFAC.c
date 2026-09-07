#include "common.h"

extern s32 func_800C30E0(void *arg0, void *arg1, s32 arg2);
extern s32 func_800644B8(s32 angle);
extern s32 func_80064584(s32 angle);
extern s32 *func_8008FAC0(void *arg0, void *arg1);
extern void func_800CD84C(void) __attribute__((noreturn));
extern void func_800CDD98(void *arg0, void *arg1, s32 arg2);

extern u8 D_800CFCB4[];

#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define S32_AT(p, off) (*(s32 *)((u8 *)(p) + (off)))

void func_800CD70C(void *arg0, void *arg1, s32 arg2) {
    s32 *entry;
    s32 state;
    u16 angle;
    u16 timer;

    if (func_800C30E0(arg0, arg1, arg2) != 0) {
        return;
    }

    angle = U16_AT(arg0, 0x86);
    U16_AT(arg0, 0x86) = angle + 0x40;
    S16_AT(arg0, 0x72) = angle + 0x440;

    U16_AT(arg1, 2) = U16_AT(arg0, 0x84) +
        func_800644B8(S16_AT(arg0, 0x86)) / (0x1000 / S16_AT(arg0, 0x84));
    U16_AT(arg1, 6) = U16_AT(arg0, 0x86) +
        func_80064584(S16_AT(arg0, 0x86)) / (0x1000 / S16_AT(arg0, 0x84)) -
        U16_AT(arg0, 0x84);

    entry = func_8008FAC0(arg0, D_800CFCB4);
    if (entry != 0) {
        state = entry[0];
        if (state != 2) {
            if (state == 0) {
                S32_AT(arg1, 0) -= entry[1];
                func_800CD84C();
            }
            S32_AT(arg1, 4) -= entry[1];
            func_800CD84C();
        }
    }

    timer = U16_AT(arg0, 0x6C) - 1;
    U16_AT(arg0, 0x6C) = timer;
    if ((s32)(timer << 16) <= 0) {
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
        func_800CDD98(arg0, arg1, arg2);
    }
}

/* MECHANISM: The seed already held arg0/arg1/arg2 in s1/s2/s3 with the retail 0x28 frame.
   A zero-footprint ASM_SCHED_BARRIER at the timer call-arm seam blocks delay-branch reorg
   from stealing move a0,s1, restoring retail's nop and exact 92-word length. */
