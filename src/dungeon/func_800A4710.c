#include "common.h"


extern s32 func_800A9E38(void *arg0);
extern s32 func_800A2BDC(void *arg0);
extern void func_8003DB94(void *arg0, s32 arg1, s8 arg2);
extern void func_80047738(void *arg0, u8 arg1, s8 arg2);
extern void func_800478B8(void *arg0);
extern s32 func_800A9F24(void);
extern void func_800A9F58(void) __attribute__((noreturn));
extern s32 func_800AA048(void);
extern void func_800AA060(void) __attribute__((noreturn));
extern s32 func_800AA22C(void);
extern s32 func_800AA234(void);
extern void func_800ACB98(void *arg0, s32 arg1, void *arg2, void *arg3);
extern void func_800ACD74(void *arg0, s32 arg1, void *arg2, void *arg3);

extern s16 D_80083228;
extern s16 D_800DCE68;
extern u8 D_8006CCF8[8];
extern u8 D_80083460[0x14];


typedef struct S_800A9E70_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x17];
    u8 unk_43;
    u8 pad_44[0x2];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_800A9E70_0;   /* arg3 in func_800A9E70 */

typedef struct S_800A9E70_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x4];
    s16 unk_94;
    u8 pad_96[0x2];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_800A9E70_1;   /* arg0 in func_800A9E70 */

typedef struct S_800A9E70_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    union { s32 * p; u8 * p2; } unk_2C;   /* accessed as both */
} S_800A9E70_2;   /* arg2 in func_800A9E70 */

typedef struct S_800A9E70_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    u8 pad_0A[0x2];
    void * unk_0C;
    s32 unk_10;
} S_800A9E70_3;   /* state in func_800A9E70 */

s32 func_800A9E70(S_800A9E70_1 *arg0, s32 arg1, S_800A9E70_2 *arg2, S_800A9E70_0 *arg3) {
    u8 *state;
    void *held;
    s32 flags14;
    s32 direction;
    s32 held_arg1 = arg1;
    s32 type;
    u16 value46;

    if (arg3->unk_14 & 0x100000) {
        direction = ((D_80083228 + arg3->unk_2A + 0x100) >> 9) & 7;
        if (arg0->unk_94 != direction) {
            if (func_800A9E38(arg3) != 0) {
                func_8003DB94(arg2, arg2->unk_2C.p[direction],
                              arg2->unk_04);
                arg0->unk_94 = direction;
                return func_800A9F24();
            }
            func_80047738(arg2, arg2->unk_2C.p2[direction],
                          arg2->unk_04);
            arg0->unk_94 = direction;
        }
        if (D_8006CCF8[direction] != 0) {
            u32 tail_value;

            tail_value = arg2->unk_14;
            tail_value |= 1;
            ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail delay-slot fill depends on it */
            func_800A9F58();
        }
        ASM_KEEP(held_arg1);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        arg2->unk_14 &= 0xFFFE;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
        func_800478B8(arg2);
        func_800AA234();
        return 1;
    }

    if (arg3->unk_1C & 0x400) {
        value46 = arg3->unk_46;
        if (value46 & 0x8000) {
            if (!(value46 & 0x4000)) {
                type = value46 & 0x3FFF;
                if (((u32)(type - 5) < 3U) || (type == 0xC)) {
                    arg3->unk_46 = value46 & 0x7FFF;
                }
            }
        }
    }

    if (!(arg2->unk_14 & 0x8000)) {
        if (arg0->unk_98 & 0x400) {
            direction = ((D_80083228 + arg3->unk_2A + 0x100) >> 9) & 7;
            if (func_800A9E38(arg3) != 0) {
                ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
                func_8003DB94(arg2, arg2->unk_2C.p[direction],
                              arg2->unk_04);
                return func_800AA048();
            }
            func_80047738(arg2, arg2->unk_2C.p2[direction],
                          arg2->unk_04);
            {
                u32 tail_value;

                tail_value = arg0->unk_98;
                tail_value &= 0xFBFF;
                ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail delay-slot fill depends on it */
            }
            func_800AA060();
        }
    } else {
        arg0->unk_98 |= 0x400;
    }

    if ((arg3->unk_1C & 0x2000) ||
        (arg3->unk_14 & 0x4000)) {
        if ((u32)(arg0->unk_9A - 0x13) >= 2U) {
            if (arg3->unk_6D == 0) {
                if (D_800DCE68 == 0) {
                    if ((func_800A2BDC(arg3) << 0x10) != 0) {
                        register s32 tail_zero ASM_REG("$2") = 0;   /* MATCH pin: load-bearing for the whole function shape */

                        ASM_KEEP(tail_zero);   /* MATCH pin: retail delay-slot contents depend on it */
                        return func_800AA234();
                    }
                    goto block_16;
                }
                state = D_80083460;
                held = ((S_800A9E70_3 *)state)->unk_0C;
                if (held != arg3) {
                    if ((((S_800A9E70_3 *)state)->unk_10 == 0) && (held == 0) &&
                        (((S_800A9E70_3 *)state)->unk_08 == 0) &&
                        !(((S_800A9E70_3 *)state)->unk_02 & 0x2008) &&
                        (arg3->unk_43 == 0xFD)) {
                        ((S_800A9E70_3 *)state)->unk_0C = arg3;
                        goto block_15;
                    }
                } else {
                block_15:
                    if (arg3->unk_43 == 0xFD) {
                    block_16:
                        if (arg3->unk_1C & 0x400000) {
                            arg0->unk_8C = 0;
                            flags14 = arg3->unk_14;
                            arg3->unk_1C &= 0xFFBFFFFF;
                            if (flags14 & 0x20000000) {
                                arg3->unk_14 = flags14 | 0x400000;
                                func_800ACB98(arg0, held_arg1, arg2, arg3);
                                func_800AA234();
                                return 0;
                            }
                            arg3->unk_14 = flags14 & 0xFFBFFFFF;
                            arg0->unk_9A = (flags14 & 0x4000) ? 1 : 2;
                            return func_800AA22C();
                        }
                        if (arg3->unk_1C & 0x02000000) {
                            arg0->unk_8C = 0;
                            arg3->unk_71 = 0;
                            arg3->unk_1C &= 0xFDFFFFFF;
                            if (arg3->unk_14 & 0x20000000) {
                                func_800ACD74(arg0, held_arg1, arg2, arg3);
                                func_800AA234();
                                return 0;
                            }
                            arg0->unk_9A = 0;
                            arg0->unk_9B = 0;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

/* MECHANISM: A held arg1 in s4, kept live after the first direction region, preserves
   the 0x28 s3/s4/s2/s1/s0 frame without fencing either region's retail schedule.
   Splitting the no-call type local yields a0; the isolated v0-zero edge pin fills
   func_800A2BDC's branch delay while the two tail-value pins preserve dispatcher tails. */
