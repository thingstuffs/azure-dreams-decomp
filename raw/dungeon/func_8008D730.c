#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_800419EC();
extern s32 func_80042900();
extern s32 func_80042B68();
extern s32 func_80048A44();
extern s32 func_80092F30();
extern s32 func_8009307C();
extern void func_800930C4(void) __attribute__((noreturn));
extern s32 func_800997FC();
extern s32 func_800A2B04();

extern u16 D_80013714;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_80083460_count __asm__("D_80083460");
extern s32 D_8008ACDC;
extern u8 D_800DCFF8[];
extern u8 D_800E0597;
extern u8 D_800E05C3;

void func_80092E90(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *savedArg3 ASM_REG("$21") = arg3;
    register void *actorBase;
    s32 found;
    s32 adjusted;
    s32 pixel;
    register s32 initArg ASM_REG("$4");
    register s32 loopResult ASM_REG("$2");
    s16 count;
    s16 divisor;
    s16 *global;
    u16 rawCount;
    u8 state;
    void *countBase;
    void *endBase;
    void *node;

    global = (s16 *)&D_80083460;
    divisor = FIELD(global, s16, 4);
    if (divisor != 0) {
        pixel = FIELD(arg2, u8, 0x24) << 6;
        adjusted = FIELD(arg1, s16, 2) - 0x20;
        FIELD(arg1, s32, 0xC) =
            ((pixel - adjusted) << 16) / divisor;
        adjusted = FIELD(arg1, s16, 6);
        adjusted -= 0x20;
        pixel = FIELD(arg2, u8, 0x25) << 6;
        ASM_MEM_BARRIER();
        FIELD(arg1, s32, 0x10) =
            ((pixel - adjusted) << 16) / FIELD(global, s16, 4);
        func_80092F30(divisor, global);
        return;
    }

    FIELD(arg1, s32, 0xC) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    ASM_SCHED_BARRIER();
    countBase = &D_80083460_count;
    count = FIELD(countBase, s16, 4);
    rawCount = FIELD(countBase, volatile u16, 4);
    if (count != 0) {
        FIELD(countBase, u16, 4) = rawCount - 1;
    }

    state = FIELD(arg0, u8, 0x9B);
    if (state == 0) {
        goto state0;
    }
    if (state == 1) {
        goto state1;
    }
    func_800930C4();

state0:
        initArg = 0x10;
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            return;
        }
        func_800419EC(initArg, 8);
        FIELD(arg2, void *, 0x2C) = D_800DCFF8;
        func_80048A44(
            arg2,
            D_800DCFF8[((D_80083228 + FIELD(savedArg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0,
            1);
        FIELD(arg0, u8, 0x9B)++;
        func_800930C4();

state1:
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            return;
        }
        ASM_SCHED_BARRIER();

        found = 0;
        if (!(D_80013714 & 8)) {
            node = (u8 *)FIELD(savedArg3, void *, 0x5C) + 0x20;
            actorBase = D_80082E80;
            do {
                if ((FIELD(actorBase, s8, 0x26) ==
                     FIELD(FIELD(node, void *, -0x14), s8, 0x26)) &&
                    ((func_80042900(node, 1) << 16) != 0)) {
                    func_80042B68(node, 1);
                    found = 1;
                }
                node = (u8 *)FIELD(node, void *, 0x5C) + 0x20;
            } while (node != savedArg3);

            loopResult = found;
            if (loopResult != 0) {
#ifndef NON_MATCHING
                register u32 page ASM_REG("$2") = 0x800E0000;
                ASM_KEEP(page);
                func_8009307C((void *)(page + 0x597));
#else
                func_8009307C(&D_800E0597);
#endif
                return;
            }
#ifndef NON_MATCHING
            ASM_CLOBBER("$2");
            {
                register u32 page ASM_REG("$2") = 0x800E0000;
                register void *message ASM_REG("$4");
                ASM_KEEP(page);
                message = (void *)(page + 0x5C3);
                ASM_KEEP(message);
                func_800997FC(message);
            }
#else
            func_800997FC(&D_800E05C3);
#endif
        }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    FIELD(arg0, void *, 0x8C) = &D_8008ACDC;
    endBase = &D_80083460;
    FIELD(endBase, u16, 0xA)--;
}

/* MECHANISM: A reload barrier plus a same-address alias/fence rematerializes the count base after the zero stores.
   Explicit state labels remove the late default block; held a0 arguments fill the case-0 slot and preserve the func_800997FC nop. */
