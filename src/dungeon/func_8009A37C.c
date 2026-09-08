#include "common.h"

extern void *D_80010248[];
extern u8 D_80081484[];
extern u8 *D_800E3D7C;
extern void func_8009FB2C(s32) __attribute__((noreturn));

u8 *func_8009FADC(s32 arg0) {
    s16 n = arg0 - 1;
    if (n < 0x14) {
        u8 *result =
            (u8 *)(0x80010248 + (n * (s32)sizeof(void *)));

        ASM_TAILSLOT_PIN(result);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        func_8009FB2C(n);
    }
    if (n != 0x14) {
        u8 *result =
            *(u8 **)(D_800E3D7C + 0xF0);

        ASM_TAILSLOT_PIN(result);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        func_8009FB2C(n);
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    return D_80081484;
}

/* MECHANISM: Frameless s16 selector preserves the retail a0 lifetime and CFG.
   Pinned v0 results plus the noreturn callee reproduce both continuation tails.
   Raw table addressing and the final fence place both page loads in retail slots. */
