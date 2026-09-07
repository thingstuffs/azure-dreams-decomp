#include "common.h"
#include "records/Rec_D_80082E80.h"


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


typedef struct S_80170A58_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170A58_0;   /* arg1 in func_80170A58 */


typedef struct S_80170A58_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80170A58_2;   /* state in func_80170A58 */

void func_80170A58(void *arg0, S_80170A58_0 *arg1, void *arg2)
{
    S_80170A58_2 *state = arg0;
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
        cb = (*(Callback *)((u8 *)arg0 + 0x8C));
        if (cb == (Callback)D_80171014) {
            cb(arg0, arg1, arg2, arg0);
        } else {
            (*(u8 *)((u8 *)arg0 + 0x71)) &= 0x7F;
        }
        return;
    }

    old_state = (s8)(*(u8 *)((u8 *)arg0 + 0x6D));
    if (func_800A9E70(arg0, arg1, arg2, arg0) != 0) {
        return;
    }

    cb2 = (*(Callback *)((u8 *)arg0 + 0x8C));
    if (cb2 != 0) {
        cb2(arg0, arg1, arg2, arg0);
    }
    D_8017426C[(*(u8 *)((u8 *)arg0 + 0x9A))](arg0, arg1, arg2, arg0);
    if (old_state != (*(s8 *)((u8 *)arg0 + 0x6D))) {
        func_800AA36C(arg0, arg1, arg2, arg0);
    }

    arg1->unk_00.at00.v += arg1->unk_0C;
    arg1->unk_04.at00.v += arg1->unk_10;

    if (!((*(s32 *)((u8 *)arg0 + 0x1C)) & 0x40000) && !((*(u16 *)((u8 *)arg0 + 0x98)) & 8)) {
        arg1->unk_14 += (*(s8 *)((u8 *)arg0 + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)arg0 + 0x9D)) = (*(u8 *)((u8 *)arg0 + 0x9D)) + 1;
    } else {
        (*(u8 *)((u8 *)arg0 + 0x9D)) = 0;
    }
    (*(s32 *)((u8 *)arg0 + 0x90)) += arg1->unk_14;

    part_flags = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v;
    if (!(part_flags & 0x8000)) {
        dir = ((D_80083228 + state->unk_2A + 0x100) >> 9) & 7;
        idx = dir;
        if ((*(s16 *)((u8 *)arg0 + 0x94)) != idx) {
            func_80047738(arg2, ((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8[idx],
                          ((Rec_D_80082E80 *)arg2)->unk_04.as_s8);
            (*(s16 *)((u8 *)arg0 + 0x94)) = dir;
        }
        if (D_8006CCF8[idx] != 0) {
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 1;
        } else {
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xFFFE;
        }
        func_800A020C(state->unk_1C, (u8 *)arg2 + 0xC);
        if (!(state->unk_1C & 0x20)) {
            if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x40)) {
                func_800478B8(arg2);
            }
        } else {
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x7000;
            state->unk_1C &= 0xFFFBFFFF;
        }

        flags = state->unk_1C;
        flags &= 0xF7FFFFFF;
        state->unk_1C = flags;
        flags &= 0x40000;
        if (flags != 0) {
            if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x40)) {
                if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 == D_8017420C) {
                    u16 count = (*(u16 *)((u8 *)arg0 + 0x9E));
                    (*(u16 *)((u8 *)arg0 + 0x9E)) = count + 1;
                    (*(s32 *)((u8 *)arg0 + 0xA0)) += func_800644B8((s16)count * 0xAA) << 5;
                }
            }
            if (!((*(u16 *)((u8 *)arg0 + 0x98)) & 8)) {
                func_800BCB04(arg1->unk_00.at02.v, arg1->unk_04.at02.v,
                              (s16)(state->unk_88 - 0x20));
                lo = -0x20;
                hs = (*(s16 *)((u8 *)arg0 + 0x92));
                hu = (*(u16 *)((u8 *)arg0 + 0x92));
                if (hs > lo) {
                    (*(u16 *)((u8 *)arg0 + 0x92)) = hu - 8;
                } else if (hs < -0x28) {
                    (*(u16 *)((u8 *)arg0 + 0x92)) = hu + 8;
                }
            }
        } else {
            s32 saved = (*(s32 *)((u8 *)arg0 + 0xA0));
            (*(u16 *)((u8 *)arg0 + 0x9E)) = 0;
            (*(s32 *)((u8 *)arg0 + 0xA0)) = 0;
            (*(s32 *)((u8 *)arg0 + 0x90)) -= saved;
            if (!((*(u16 *)((u8 *)arg0 + 0x98)) & 8)) {
                delta = func_800BCB04(arg1->unk_00.at02.v, arg1->unk_04.at02.v,
                                      (s16)(state->unk_88 - 0x20)) -
                        state->unk_88;
                if (delta < (*(s16 *)((u8 *)arg0 + 0x92))) {
                    (*(s16 *)((u8 *)arg0 + 0x92)) = delta;
                    (*(u8 *)((u8 *)arg0 + 0x9D)) = 0;
                    arg1->unk_14 = 0;
                    state->unk_1C |= 0x8000000;
                }
            }
        }
    } else {
        if (!(part_flags & 0x800)) {
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = part_flags | 0x7000;
        } else {
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = part_flags & 0x8FFF;
        }

        flags = state->unk_1C;
        flags &= 0xF7FFFFFF;
        state->unk_1C = flags;
        flags &= 0x40000;
        if (flags == 0) {
            s32 saved = (*(s32 *)((u8 *)arg0 + 0xA0));
            (*(u16 *)((u8 *)arg0 + 0x9E)) = 0;
            (*(s32 *)((u8 *)arg0 + 0xA0)) = 0;
            (*(s32 *)((u8 *)arg0 + 0x90)) -= saved;
            if (!((*(u16 *)((u8 *)arg0 + 0x98)) & 8)) {
                delta = func_800BCB04(arg1->unk_00.at02.v, arg1->unk_04.at02.v,
                                      (s16)(state->unk_88 - 0x20)) -
                        state->unk_88;
                if (delta < (*(s16 *)((u8 *)arg0 + 0x92))) {
                    (*(s16 *)((u8 *)arg0 + 0x92)) = delta;
                    (*(u8 *)((u8 *)arg0 + 0x9D)) = 0;
                    arg1->unk_14 = 0;
                    state->unk_1C |= 0x8000000;
                }
            }
        } else {
            if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x40)) {
                if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 == D_8017420C) {
                    u16 count = (*(u16 *)((u8 *)arg0 + 0x9E));
                    (*(u16 *)((u8 *)arg0 + 0x9E)) = count + 1;
                    (*(s32 *)((u8 *)arg0 + 0xA0)) += func_800644B8((s16)count * 0xAA) << 5;
                }
            }
            if (!((*(u16 *)((u8 *)arg0 + 0x98)) & 8)) {
                func_800BCB04(arg1->unk_00.at02.v, arg1->unk_04.at02.v,
                              (s16)(state->unk_88 - 0x20));
                lo = -0x20;
                hs = (*(s16 *)((u8 *)arg0 + 0x92));
                hu = (*(u16 *)((u8 *)arg0 + 0x92));
                if (hs > lo) {
                    (*(u16 *)((u8 *)arg0 + 0x92)) = hu - 8;
                } else if (hs < -0x28) {
                    (*(u16 *)((u8 *)arg0 + 0x92)) = hu + 8;
                }
            }
        }
    }

    flags = state->unk_1C;
    if (flags & 0x40000000) {
        state->unk_1C = flags & 0xBFFFFFFF;
        ground = func_800BCB04((((Rec_D_80082E80 *)arg2)->unk_24 << 6) | 0x20,
                               (((Rec_D_80082E80 *)arg2)->unk_25 << 6) | 0x20,
                               (s16)(state->unk_88 - 0x20));
        if ((s16)ground < 0x200) {
            (*(s16 *)((u8 *)arg0 + 0x92)) =
                (*(u16 *)((u8 *)arg0 + 0x92)) + (state->unk_88 - ground);
            state->unk_88 = ground;
        }
    }

    arg1->unk_0A = state->unk_88 + (*(u16 *)((u8 *)arg0 + 0x92)) -
                            (*(u16 *)((u8 *)arg0 + 0xA2));
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x40;
}

/* MECHANISM: baseline rebuild (eval 1) */
