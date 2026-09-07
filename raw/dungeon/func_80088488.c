#include "common.h"

extern void func_80048A44(void *, u8, s32, s32);
extern void func_8008D94C(void *, void *, void *, void *);
extern void func_8008DCEC(void);
extern void func_8008DDC8(void);
extern s32 func_80094F74(void *, void *, void *, void *);
extern void func_800A2B04(void *, u8, u8);

extern u16 D_80013714;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008ACDC;
extern u8 D_800DD050[];

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

void func_8008DBE8(void *arg0, void *arg1, void *arg2, void *arg3) {
    void *status = &D_80083460;
    void *late_status;
    register u32 page ASM_REG("$2");
    s32 mode;
    s32 quotient;
    s32 coordinate;
    s32 divisor2;
    s16 timer;
    u16 flags;

    if (FIELD(status, u16, 2) & 0x80) {
        FIELD(status, s16, 4) = 0;
    }

    timer = FIELD(status, s16, 4);
    if (timer != 0) {
        quotient =
            ((((FIELD(arg2, u8, 0x24) << 6) + 0x20) << 16) -
             FIELD(arg1, s32, 0)) /
            timer;
        coordinate = FIELD(arg1, s32, 4);
        FIELD(arg1, s32, 0xC) = quotient;
        ASM_MEM_BARRIER();
        divisor2 = FIELD(status, s16, 4);
        FIELD(arg1, s32, 0x10) =
            ((((FIELD(arg2, u8, 0x25) << 6) + 0x20) << 16) -
             coordinate) /
            divisor2;
    }

    if (FIELD(arg0, u16, 0xA2) & 0x100) {
        ASM_SCHED_BARRIER();
        mode = FIELD(status, s16, 4);
        if (D_80013714 & 8) {
            if (mode != 3) {
                func_8008DCEC();
                return;
            }
        } else if (mode != 6) {
            goto continue_update;
        }

        func_8008D94C(arg0, arg1, arg2, arg3);
        func_8008DDC8();
        return;
    }

continue_update:
    flags = FIELD(arg0, u16, 0xA2);
    if (!(flags & 0x10)) {
        if (FIELD(arg2, u8 *, 0x2C) != D_800DD050) {
            FIELD(arg0, u16, 0xA2) = flags | 1;
            FIELD(arg2, u8 *, 0x2C) = D_800DD050;
            func_80048A44(
                arg2,
                D_800DD050[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0,
                1);
        }
    }

    page = 0x80080000;
    ASM_KEEP(page);
    late_status = (void *)(page + 0x3460);
    timer = FIELD(late_status, s16, 4) - 1;
    FIELD(late_status, s16, 4) = timer;
    if (timer > 0) {
        return;
    }

    FIELD(late_status, s16, 4) = 0;
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

    FIELD(arg2, u16, 0x14) |= 0x4000;
    if ((s16)func_80094F74(arg0, arg1, arg2, arg3) > 0) {
        FIELD(arg0, s32, 0x8C) = (s32)&D_8008ACDC;
    }
}

/* MECHANISM: Separate s32 quotient/coordinate/divisor pseudos plus ASM_MEM_BARRIER reuse
   $a0 for the coordinate preload and force the signed timer reload into $v1.
   Widened mode + ASM_SCHED_BARRIER preserve the branch nop; zero-arg DCEC and
   the post-merge pinned page reproduce the tail ABI and late $v0 coloring. */
