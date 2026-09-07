#include "common.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_D_800E3D7C.h"



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

    state = ((Rec_func_800AA258_arg2 *)arg2)->unk_2C.as_pu8;
    if (state == D_801740E0) {
        if (((Rec_func_800AA258_arg2 *)arg2)->unk_04 == 0x103) {
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801740E8;
            func_80047784(
                arg2,
                D_801740E8[
                    ((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
        }
        goto main_call;
    }
    if (state != D_801740E8) {
        goto main_call;
    }
    if (((Rec_func_800AA258_arg2 *)arg2)->unk_04 != 0x103) {
        goto main_call;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801740E0;
    func_80047784(
        arg2,
        D_801740E0[
            ((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);

main_call:
    if (func_800AC82C(arg0, arg1, arg2, arg3) != 0) {
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            ((S_80173E00_2 *)arg0)->unk_8C = &D_801714D4;
        }
    } else if ((((Rec_func_800AA258_arg2 *)arg2)->unk_2C.as_pu8 == D_80174158) &&
               !(((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x208)) {
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801740E0;
        func_80047784(
            arg2,
            D_801740E0[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
    }
}

/* MECHANISM: Four call-live arguments naturally occupy s2/s3/s0/s1 and make
   the 0x28 frame; the apparent callees are local CFG joins. Duplicated direct
   E0/E8 update arms cross-jump into one suffix with a1-held byte-table bases. */
