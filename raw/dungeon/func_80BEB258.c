#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef void (*Callback)(void *, void *, void *, void *);

extern void func_80047738(void *, u8, s8);
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern void func_800A020C(s32, void *);
extern s32 func_800A9E70(void *, void *, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s32 func_800BCB04(s32, s32, s32);

extern u8 D_8006CCF8[];
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80171014[];
extern u8 D_8017420C[];
extern Callback D_8017426C[];

void func_80170A58(void *arg0, void *arg1, void *arg2)
{
    void *state = arg0;
    s16 old_state;
    s32 dir;
    u8 idx;
    s16 hs;
    u16 hu;
    s32 lo;
    s16 delta;
    s32 ground;
    u16 part_flags;
    s32 flags;
    Callback cb;
    Callback cb2;

    if (D_80083462 & 0x2000) {
        cb = FIELD(arg0, Callback, 0x8C);
        if (cb == (Callback)D_80171014) {
            cb(arg0, arg1, arg2, arg0);
        } else {
            FIELD(arg0, u8, 0x71) &= 0x7F;
        }
        return;
    }

    old_state = (s8)FIELD(arg0, u8, 0x6D);
    if (func_800A9E70(arg0, arg1, arg2, arg0) != 0) {
        return;
    }

    cb2 = FIELD(arg0, Callback, 0x8C);
    if (cb2 != 0) {
        cb2(arg0, arg1, arg2, arg0);
    }
    D_8017426C[FIELD(arg0, u8, 0x9A)](arg0, arg1, arg2, arg0);
    if (old_state != FIELD(arg0, s8, 0x6D)) {
        func_800AA36C(arg0, arg1, arg2, arg0);
    }

    FIELD(arg1, s32, 0x0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 0x4) += FIELD(arg1, s32, 0x10);

    if (!(FIELD(arg0, s32, 0x1C) & 0x40000) && !(FIELD(arg0, u16, 0x98) & 8)) {
        FIELD(arg1, s32, 0x14) += FIELD(arg0, s8, 0x9D) * 0x14000;
        FIELD(arg0, u8, 0x9D) = FIELD(arg0, u8, 0x9D) + 1;
    } else {
        FIELD(arg0, u8, 0x9D) = 0;
    }
    FIELD(arg0, s32, 0x90) += FIELD(arg1, s32, 0x14);

    part_flags = FIELD(arg2, u16, 0x14);
    if (!(part_flags & 0x8000)) {
        dir = ((D_80083228 + FIELD(state, s16, 0x2A) + 0x100) >> 9) & 7;
        idx = dir;
        if (FIELD(arg0, s16, 0x94) != idx) {
            func_80047738(arg2, FIELD(arg2, u8 *, 0x2C)[idx],
                          FIELD(arg2, s8, 0x4));
            FIELD(arg0, s16, 0x94) = dir;
        }
        if (D_8006CCF8[idx] != 0) {
            FIELD(arg2, u16, 0x14) |= 1;
        } else {
            FIELD(arg2, u16, 0x14) &= 0xFFFE;
        }
        func_800A020C(FIELD(state, s32, 0x1C), (u8 *)arg2 + 0xC);
        if (!(FIELD(state, s32, 0x1C) & 0x20)) {
            if (!(FIELD(arg2, u16, 0x14) & 0x40)) {
                func_800478B8(arg2);
            }
        } else {
            FIELD(arg2, u16, 0x14) |= 0x7000;
            FIELD(state, s32, 0x1C) &= 0xFFFBFFFF;
        }

        flags = FIELD(state, s32, 0x1C);
        flags &= 0xF7FFFFFF;
        FIELD(state, s32, 0x1C) = flags;
        flags &= 0x40000;
        if (flags != 0) {
            if (!(FIELD(arg2, u16, 0x14) & 0x40)) {
                if (FIELD(arg2, u8 *, 0x2C) == D_8017420C) {
                    u16 count = FIELD(arg0, u16, 0x9E);
                    FIELD(arg0, u16, 0x9E) = count + 1;
                    FIELD(arg0, s32, 0xA0) += func_800644B8((s16)count * 0xAA) << 5;
                }
            }
            if (!(FIELD(arg0, u16, 0x98) & 8)) {
                func_800BCB04(FIELD(arg1, u16, 0x2), FIELD(arg1, u16, 0x6),
                              (s16)(FIELD(state, u16, 0x88) - 0x20));
                lo = -0x20;
                hs = FIELD(arg0, s16, 0x92);
                hu = FIELD(arg0, u16, 0x92);
                if (hs > lo) {
                    FIELD(arg0, u16, 0x92) = hu - 8;
                } else if (hs < -0x28) {
                    FIELD(arg0, u16, 0x92) = hu + 8;
                }
            }
        } else {
            s32 saved = FIELD(arg0, s32, 0xA0);
            FIELD(arg0, u16, 0x9E) = 0;
            FIELD(arg0, s32, 0xA0) = 0;
            FIELD(arg0, s32, 0x90) -= saved;
            if (!(FIELD(arg0, u16, 0x98) & 8)) {
                delta = func_800BCB04(FIELD(arg1, u16, 0x2), FIELD(arg1, u16, 0x6),
                                      (s16)(FIELD(state, u16, 0x88) - 0x20)) -
                        FIELD(state, u16, 0x88);
                if (delta < FIELD(arg0, s16, 0x92)) {
                    FIELD(arg0, s16, 0x92) = delta;
                    FIELD(arg0, u8, 0x9D) = 0;
                    FIELD(arg1, s32, 0x14) = 0;
                    FIELD(state, s32, 0x1C) |= 0x8000000;
                }
            }
        }
    } else {
        if (!(part_flags & 0x800)) {
            FIELD(arg2, u16, 0x14) = part_flags | 0x7000;
        } else {
            FIELD(arg2, u16, 0x14) = part_flags & 0x8FFF;
        }

        flags = FIELD(state, s32, 0x1C);
        flags &= 0xF7FFFFFF;
        FIELD(state, s32, 0x1C) = flags;
        flags &= 0x40000;
        if (flags == 0) {
            s32 saved = FIELD(arg0, s32, 0xA0);
            FIELD(arg0, u16, 0x9E) = 0;
            FIELD(arg0, s32, 0xA0) = 0;
            FIELD(arg0, s32, 0x90) -= saved;
            if (!(FIELD(arg0, u16, 0x98) & 8)) {
                delta = func_800BCB04(FIELD(arg1, u16, 0x2), FIELD(arg1, u16, 0x6),
                                      (s16)(FIELD(state, u16, 0x88) - 0x20)) -
                        FIELD(state, u16, 0x88);
                if (delta < FIELD(arg0, s16, 0x92)) {
                    FIELD(arg0, s16, 0x92) = delta;
                    FIELD(arg0, u8, 0x9D) = 0;
                    FIELD(arg1, s32, 0x14) = 0;
                    FIELD(state, s32, 0x1C) |= 0x8000000;
                }
            }
        } else {
            if (!(FIELD(arg2, u16, 0x14) & 0x40)) {
                if (FIELD(arg2, u8 *, 0x2C) == D_8017420C) {
                    u16 count = FIELD(arg0, u16, 0x9E);
                    FIELD(arg0, u16, 0x9E) = count + 1;
                    FIELD(arg0, s32, 0xA0) += func_800644B8((s16)count * 0xAA) << 5;
                }
            }
            if (!(FIELD(arg0, u16, 0x98) & 8)) {
                func_800BCB04(FIELD(arg1, u16, 0x2), FIELD(arg1, u16, 0x6),
                              (s16)(FIELD(state, u16, 0x88) - 0x20));
                lo = -0x20;
                hs = FIELD(arg0, s16, 0x92);
                hu = FIELD(arg0, u16, 0x92);
                if (hs > lo) {
                    FIELD(arg0, u16, 0x92) = hu - 8;
                } else if (hs < -0x28) {
                    FIELD(arg0, u16, 0x92) = hu + 8;
                }
            }
        }
    }

    flags = FIELD(state, s32, 0x1C);
    if (flags & 0x40000000) {
        FIELD(state, s32, 0x1C) = flags & 0xBFFFFFFF;
        ground = func_800BCB04((FIELD(arg2, u8, 0x24) << 6) | 0x20,
                               (FIELD(arg2, u8, 0x25) << 6) | 0x20,
                               (s16)(FIELD(state, u16, 0x88) - 0x20));
        if ((s16)ground < 0x200) {
            FIELD(arg0, s16, 0x92) =
                FIELD(arg0, u16, 0x92) + (FIELD(state, u16, 0x88) - ground);
            FIELD(state, u16, 0x88) = ground;
        }
    }

    FIELD(arg1, s16, 0xA) = FIELD(state, u16, 0x88) + FIELD(arg0, u16, 0x92) -
                            FIELD(arg0, u16, 0xA2);
    FIELD(arg2, u16, 0x14) |= 0x40;
}

/* MECHANISM: baseline rebuild (eval 1) */
