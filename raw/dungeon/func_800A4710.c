#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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

s32 func_800A9E70(void *arg0, s32 arg1, void *arg2, void *arg3) {
    u8 *state;
    void *held;
    s32 flags14;
    s32 direction;
    register s32 held_arg1 ASM_REG("$20") = arg1;
    s32 type;
    u16 value46;

    if (FIELD(arg3, s32, 0x14) & 0x100000) {
        direction = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
        if (FIELD(arg0, s16, 0x94) != direction) {
            if (func_800A9E38(arg3) != 0) {
                func_8003DB94(arg2, FIELD(arg2, s32 *, 0x2C)[direction],
                              FIELD(arg2, s8, 4));
                FIELD(arg0, s16, 0x94) = direction;
                return func_800A9F24();
            }
            func_80047738(arg2, FIELD(arg2, u8 *, 0x2C)[direction],
                          FIELD(arg2, s8, 4));
            FIELD(arg0, s16, 0x94) = direction;
        }
        if (D_8006CCF8[direction] != 0) {
            register u32 tail_value ASM_REG("$2");

            tail_value = FIELD(arg2, u16, 0x14);
            tail_value |= 1;
            ASM_TAILSLOT_PIN(tail_value);
            func_800A9F58();
        }
        ASM_KEEP(held_arg1);
        FIELD(arg2, u16, 0x14) &= 0xFFFE;
        ASM_SCHED_BARRIER();
        func_800478B8(arg2);
        func_800AA234();
        return 1;
    }

    if (FIELD(arg3, s32, 0x1C) & 0x400) {
        value46 = FIELD(arg3, u16, 0x46);
        if (value46 & 0x8000) {
            if (!(value46 & 0x4000)) {
                type = value46 & 0x3FFF;
                if (((u32)(type - 5) < 3U) || (type == 0xC)) {
                    FIELD(arg3, u16, 0x46) = value46 & 0x7FFF;
                }
            }
        }
    }

    if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
        if (FIELD(arg0, u16, 0x98) & 0x400) {
            direction = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
            if (func_800A9E38(arg3) != 0) {
                ASM_SCHED_BARRIER();
                func_8003DB94(arg2, FIELD(arg2, s32 *, 0x2C)[direction],
                              FIELD(arg2, s8, 4));
                return func_800AA048();
            }
            func_80047738(arg2, FIELD(arg2, u8 *, 0x2C)[direction],
                          FIELD(arg2, s8, 4));
            {
                register u32 tail_value ASM_REG("$2");

                tail_value = FIELD(arg0, u16, 0x98);
                tail_value &= 0xFBFF;
                ASM_TAILSLOT_PIN(tail_value);
            }
            func_800AA060();
        }
    } else {
        FIELD(arg0, u16, 0x98) |= 0x400;
    }

    if ((FIELD(arg3, s32, 0x1C) & 0x2000) ||
        (FIELD(arg3, s32, 0x14) & 0x4000)) {
        if ((u32)(FIELD(arg0, u8, 0x9A) - 0x13) >= 2U) {
            if (FIELD(arg3, s8, 0x6D) == 0) {
                if (D_800DCE68 == 0) {
                    if ((func_800A2BDC(arg3) << 0x10) != 0) {
                        register s32 tail_zero ASM_REG("$2") = 0;

                        ASM_KEEP(tail_zero);
                        return func_800AA234();
                    }
                    goto block_16;
                }
                state = D_80083460;
                held = FIELD(state, void *, 0xC);
                if (held != arg3) {
                    if ((FIELD(state, s32, 0x10) == 0) && (held == 0) &&
                        (FIELD(state, s16, 8) == 0) &&
                        !(FIELD(state, u16, 2) & 0x2008) &&
                        (FIELD(arg3, u8, 0x43) == 0xFD)) {
                        FIELD(state, void *, 0xC) = arg3;
                        goto block_15;
                    }
                } else {
                block_15:
                    if (FIELD(arg3, u8, 0x43) == 0xFD) {
                    block_16:
                        if (FIELD(arg3, s32, 0x1C) & 0x400000) {
                            FIELD(arg0, s32, 0x8C) = 0;
                            flags14 = FIELD(arg3, s32, 0x14);
                            FIELD(arg3, s32, 0x1C) &= 0xFFBFFFFF;
                            if (flags14 & 0x20000000) {
                                FIELD(arg3, s32, 0x14) = flags14 | 0x400000;
                                func_800ACB98(arg0, held_arg1, arg2, arg3);
                                func_800AA234();
                                return 0;
                            }
                            FIELD(arg3, s32, 0x14) = flags14 & 0xFFBFFFFF;
                            FIELD(arg0, u8, 0x9A) = (flags14 & 0x4000) ? 1 : 2;
                            return func_800AA22C();
                        }
                        if (FIELD(arg3, s32, 0x1C) & 0x02000000) {
                            FIELD(arg0, s32, 0x8C) = 0;
                            FIELD(arg3, u8, 0x71) = 0;
                            FIELD(arg3, s32, 0x1C) &= 0xFDFFFFFF;
                            if (FIELD(arg3, s32, 0x14) & 0x20000000) {
                                func_800ACD74(arg0, held_arg1, arg2, arg3);
                                func_800AA234();
                                return 0;
                            }
                            FIELD(arg0, u8, 0x9A) = 0;
                            FIELD(arg0, u8, 0x9B) = 0;
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
