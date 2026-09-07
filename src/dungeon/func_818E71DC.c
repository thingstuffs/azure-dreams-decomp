#include "common.h"

typedef struct S_800249DC_0_pre {
    u16 unk_00;
} S_800249DC_0_pre;   /* the 0x2 bytes before arg0 in func_800249DC, addressed as arg0[-1] */

typedef struct S_800249DC_0 {
    void * unk_00;
    u8 pad_04[0x18];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    u8 pad_28[0xC];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u8 pad_40[0x8];
    u16 unk_48;
} S_800249DC_0;   /* arg0 in func_800249DC */

typedef struct S_800249DC_1 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800249DC_1;   /* temp_ptr in func_800249DC */

typedef struct S_800249DC_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800249DC_2;   /* arg1 in func_800249DC */

typedef struct S_800249DC_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x6];
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    u8 pad_10[0x4];
    u16 unk_14;
} S_800249DC_3;   /* arg2 in func_800249DC */



extern void func_800478B8(void *arg0);
extern s32 D_800814A0[3];

void func_800249DC(void *arg0, S_800249DC_2 *arg1, S_800249DC_3 *arg2) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 diff;
    u16 temp_v0;
    S_800249DC_1 *temp_ptr;

    temp_ptr = ((S_800249DC_0 *)arg0)->unk_00;
    temp_ptr->unk_10 =
        (s32)(temp_ptr->unk_10 | 0x8000);

    temp_v0 = ((S_800249DC_0 *)arg0)->unk_48 - 1;
    ((S_800249DC_0 *)arg0)->unk_48 = temp_v0;
    if ((temp_v0 << 16) > 0) {
        ((S_800249DC_0 *)arg0)->unk_1C =
            (s32)(((S_800249DC_0 *)arg0)->unk_1C + ((S_800249DC_0 *)arg0)->unk_34);
        ((S_800249DC_0 *)arg0)->unk_20 =
            (s32)(((S_800249DC_0 *)arg0)->unk_20 + ((S_800249DC_0 *)arg0)->unk_38);
        ((S_800249DC_0 *)arg0)->unk_24 =
            (s32)(((S_800249DC_0 *)arg0)->unk_24 + ((S_800249DC_0 *)arg0)->unk_3C);
    }

    diff = ((S_800249DC_0 *)arg0)->unk_1C;
    temp_a0 = arg1->unk_00;
    diff -= temp_a0;
    arg1->unk_00 =
        (s32)(temp_a0 + (diff / 5));
    diff = ((S_800249DC_0 *)arg0)->unk_20;
    temp_a0_2 = arg1->unk_04;
    diff -= temp_a0_2;
    arg1->unk_04 =
        (s32)(temp_a0_2 + (diff / 5));
    diff = ((S_800249DC_0 *)arg0)->unk_24;
    temp_a0_3 = arg1->unk_08;
    diff -= temp_a0_3;
    arg1->unk_08 =
        (s32)(temp_a0_3 + (diff / 5));

    func_800478B8(arg2);
    if (arg2->unk_14 & 0x6000) {
        arg2->unk_04 = 0;
        arg2->unk_05 = 0;
    }

    if ((u8)arg2->unk_0C.u8 >= 0x60U) {
        ((S_800249DC_0_pre *)arg0)[-1].unk_00 =
            (u16)(((S_800249DC_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
        return;
    }

    arg2->unk_0C.s32 += 0xC0C0C;
}
