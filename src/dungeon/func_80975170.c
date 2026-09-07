#include "common.h"

typedef struct S_80975170_0_pre {
    u16 unk_00;
} S_80975170_0_pre;   /* the 0x2 bytes before arg0 in func_80975170, addressed as arg0[-1] */

typedef struct S_80975170_0 {
    u8 pad_00[0x96];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x12];
    s16 unk_AA;
    u8 pad_AC[0x4];
    void * unk_B0;
} S_80975170_0;   /* arg0 in func_80975170 */

typedef struct S_80975170_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80975170_1;   /* arg1 in func_80975170 */

typedef struct S_80975170_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80975170_2;   /* src in func_80975170 */

typedef struct S_80975170_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
    u16 unk_1E;
} S_80975170_3;   /* arg2 in func_80975170 */


extern void func_800478B8(void *arg0);
extern s32 D_800814A0[3];


void func_80975170(void *arg0, S_80975170_1 *arg1, S_80975170_3 *arg2)
{
    s16 count;
    s32 shade;
    u16 pos;
    S_80975170_2 *src;

    src = ((S_80975170_0 *)arg0)->unk_B0;
    arg1->unk_02 = src->unk_02;
    arg1->unk_06 = src->unk_06;
    arg1->unk_0A = src->unk_0A;

    pos = arg2->unk_1E + 0x320;
    arg2->unk_1E = pos;
    arg2->unk_1C = pos;

    count = ((S_80975170_0 *)arg0)->unk_96.s - 1;
    shade = (s32)(count * 0x50) / (s16)((S_80975170_0 *)arg0)->unk_AA;
    ((S_80975170_0 *)arg0)->unk_96.s = (u16)count;
    arg2->unk_0E = (s8)shade;
    arg2->unk_0D = (s8)shade;
    arg2->unk_0C = (s8)shade;
    func_800478B8(arg2);

    if (((S_80975170_0 *)arg0)->unk_96.u <= 0) {
        ((S_80975170_0_pre *)arg0)[-1].unk_00 = (u16)(((S_80975170_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }
}
