#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_800644B8(s32);
extern s32 func_80065420(void *, void *, void *, void *);
extern void func_800C96E8(void *, void *);

s32 func_80099A1C(void *arg0, void *arg1, void *arg2)
{
    register u8 *scratch ASM_REG("$16");
    void *next;
    s32 value;

    scratch = (u8 *)0x1F800000;
    ASM_KEEP(scratch);

loop:
    FIELD(scratch, u16, 0) = FIELD(arg1, u16, 2);
    FIELD(scratch, u16, 2) = FIELD(arg1, u16, 6);
    FIELD(scratch, u16, 4) = FIELD(arg1, u16, 10);

    value = func_80065420(
        scratch,
        scratch + 0xB8,
        scratch + 0x90,
        scratch + 0x94);
    FIELD(scratch, s32, 0xC0) = value - FIELD(arg2, s16, 6);

    {
        register s32 delta ASM_REG("$2");
        u16 accum;

        delta = FIELD(arg0, u16, 0);
        accum = FIELD(scratch, u16, 0xB8);
        delta = (delta << 16) >> 17;
        ASM_KEEP(delta);
        accum -= delta;
        FIELD(scratch, u16, 0xB8) = accum;
    }
    FIELD(scratch, u16, 0xB8) +=
        (func_800644B8(
            (FIELD(arg0, s16, 0xC) << 8) +
            (FIELD(arg0, s32, 8) << 7)) *
         (FIELD(arg0, s32, 8) >> 2)) >> 9;

    func_800C96E8(arg0, scratch);

    next = FIELD(arg0, void *, -8);
    arg0 = (u8 *)next + 0x20;
    if (next != 0) {
        arg1 = FIELD(next, void *, 8);
        arg2 = FIELD(next, void *, 0xC);
        goto loop;
    }
    return 0;
}

/* MECHANISM: Recover the true-space back-edge as a local loop, keeping the current
   object/state in s1/s2 and the 0x1F800000 scratch base in pinned s0.
   Use the real four-argument scratch offsets and a word store at +0xC0; a scoped
   v0 delta pin closes the final v0/v1 allocation swap in the halfword update. */
