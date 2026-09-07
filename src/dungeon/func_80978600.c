#include "common.h"

typedef struct S_80173E00_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x26];
    u8 * unk_2C;
} S_80173E00_0;   /* arg2 in func_80173E00 */

typedef struct S_80173E00_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_80173E00_1;   /* arg3 in func_80173E00 */

typedef struct S_80173E00_2 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
} S_80173E00_2;   /* arg0 in func_80173E00 */



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

    state = ((S_80173E00_0 *)arg2)->unk_2C;
    if (state == D_801740E0) {
        if (((S_80173E00_0 *)arg2)->unk_04 == 0x103) {
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801740E8;
            func_80047784(
                arg2,
                D_801740E8[
                    ((D_80083228 + ((S_80173E00_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        goto main_call;
    }
    if (state != D_801740E8) {
        goto main_call;
    }
    if (((S_80173E00_0 *)arg2)->unk_04 != 0x103) {
        goto main_call;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801740E0;
    func_80047784(
        arg2,
        D_801740E0[
            ((D_80083228 + ((S_80173E00_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);

main_call:
    if (func_800AC82C(arg0, arg1, arg2, arg3) != 0) {
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            ((S_80173E00_2 *)arg0)->unk_8C = &D_801714D4;
        }
    } else if ((((S_80173E00_0 *)arg2)->unk_2C == D_80174158) &&
               !(((S_80173E00_1 *)arg3)->unk_1C & 0x208)) {
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801740E0;
        func_80047784(
            arg2,
            D_801740E0[((D_80083228 + ((S_80173E00_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
    }
}

/* MECHANISM: Four call-live arguments naturally occupy s2/s3/s0/s1 and make
   the 0x28 frame; the apparent callees are local CFG joins. Duplicated direct
   E0/E8 update arms cross-jump into one suffix with a1-held byte-table bases. */
