#include "common.h"

typedef void (*Callback)(void *, void *, void *, s32);

typedef struct S_8009B6B4_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8009B6B4_0;   /* arg2 in func_8009B6B4 */

typedef struct S_8009B6B4_1 {
    u8 pad_00[0x3B];
    u8 unk_3B;
} S_8009B6B4_1;   /* arg1 in func_8009B6B4 */

typedef struct S_8009B6B4_2_pre {
    u16 unk_00;
} S_8009B6B4_2_pre;   /* the 0x2 bytes before arg0 in func_8009B6B4, addressed as arg0[-1] */

typedef struct S_8009B6B4_2 {
    u8 pad_00[0x50];
    void * unk_50;
} S_8009B6B4_2;   /* arg0 in func_8009B6B4 */



extern void func_80095388(void *);
extern void func_8009539C(void *);
extern s16 func_8008F170(void *, void *);
extern void func_8008F27C(void *, void *, s16);
extern s32 func_8008F294(void *, void *);
extern void func_8008F664(void *, void *);
extern void func_8009B778(void *, void *);
extern s32 func_8008C180(s16, s16);
extern s32 func_800C1D44(u16);
extern void func_80053DA8(u32);

extern u8 D_8009B454[];
extern s16 D_800D45AA[];
extern u8 D_800FE488[];

void func_8009B6B4(void *arg0, S_8009B6B4_1 *arg1, S_8009B6B4_0 *arg2, s32 arg3) {
    s16 result;
    s32 signed_result;

    func_80095388(arg2);
    if (arg2->unk_14 > 0x200000) {
        arg2->unk_14 = 0x200000;
    }
    func_8009539C(arg2);
    result = func_8008F170(arg2, D_800FE488);
    func_8008F294(arg1, arg2);
    func_8008F664(arg1, arg2);
    signed_result = result;
    if (arg2->unk_0A >= signed_result) {
        func_8008F27C(arg1, arg2, signed_result);
        func_8009B778(arg0, arg1);
        return;
    }
    if (arg1->unk_3B != 0) {
        arg2->unk_14 = 0;
        ((Callback *)(*(void **)((u8 *)arg0 + 0x58)))[1](arg0, arg1, arg2, arg3);
    }
    if ((((S_8009B6B4_2_pre *)arg0)[-1].unk_00 & 0x8000) == 0 &&
        D_8009B454 == ((S_8009B6B4_2 *)arg0)->unk_50) {
        s32 index;

        index = func_800C1D44((u16)func_8008C180(
            arg2->unk_02, arg2->unk_06));
        if (index != 0) {
            s16 *thresholds = D_800D45AA;
            s16 height = arg2->unk_0A;
            s16 threshold = thresholds[index];

            if (height > threshold) {
                func_80053DA8(0x517);
            }
        }
    }
}
