#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, u8, s32);
extern s32 func_800AC82C(s32, s32, void *, void *);
extern s32 func_800AD9B4(void *, void *);

extern s16 D_80083228;
extern u8 D_801714D4;
extern u8 D_801740E0[];
extern u8 D_801740E8[];
extern u8 D_80174158[];

void func_80173E00(s32 arg0, s32 arg1, void *arg2, void *arg3)
{
    u8 *state;

    state = FIELD(arg2, u8 *, 0x2C);
    if (state == D_801740E0) {
        if (FIELD(arg2, u16, 4) == 0x103) {
            FIELD(arg2, u8 *, 0x2C) = D_801740E8;
            func_80047784(
                arg2,
                D_801740E8[
                    ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
        }
        goto main_call;
    }
    if (state != D_801740E8) {
        goto main_call;
    }
    if (FIELD(arg2, u16, 4) != 0x103) {
        goto main_call;
    }
    FIELD(arg2, u8 *, 0x2C) = D_801740E0;
    func_80047784(
        arg2,
        D_801740E0[
            ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);

main_call:
    if (func_800AC82C(arg0, arg1, arg2, arg3) != 0) {
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            FIELD(arg0, u8 *, 0x8C) = &D_801714D4;
        }
    } else if ((FIELD(arg2, u8 *, 0x2C) == D_80174158) &&
               !(FIELD(arg3, s32, 0x1C) & 0x208)) {
        FIELD(arg2, u8 *, 0x2C) = D_801740E0;
        func_80047784(
            arg2,
            D_801740E0[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }
}

/* MECHANISM: Four call-live arguments naturally occupy s2/s3/s0/s1 and make
   the 0x28 frame; the apparent callees are local CFG joins. Duplicated direct
   E0/E8 update arms cross-jump into one suffix with a1-held byte-table bases. */
