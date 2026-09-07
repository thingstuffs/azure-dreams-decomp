#include "common.h"
#include "m2c_compat.h"

typedef struct S_800974DC_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
    u8 pad_A4[0x5E];
    u8 unk_102;
} S_800974DC_0;   /* arg0 in func_800974DC */

typedef struct S_800974DC_1 {
    u8 pad_00[0x20];
    s16 unk_20;
    u8 pad_22[0x8];
    s16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
    void * unk_60;
} S_800974DC_1;   /* arg3 in func_800974DC */

typedef struct S_800974DC_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800974DC_2;   /* arg1 in func_800974DC */

typedef struct S_800974DC_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800974DC_3;   /* arg2 in func_800974DC */

typedef struct S_800974DC_4_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800974DC_4_pre;   /* the 0x14 bytes before temp_a2 in func_800974DC, addressed as temp_a2[-1] */

typedef struct S_800974DC_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800974DC_4;   /* temp_a2 in func_800974DC */

typedef struct S_800974DC_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_800974DC_5;   /* temp_v0_2 in func_800974DC */

typedef struct S_800974DC_6 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800974DC_6;   /* ((S_800974DC_4_pre *)temp_a2)[-1].unk_00 in func_800974DC */


extern void *D_80088B50[];
void func_8003DB94();
M2C_UNK func_80099F04();
s32 func_8009C12C();
M2C_UNK func_800A2B04();
M2C_UNK func_800C77D0();
extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern s16 D_80083228;
extern u8 D_80083460[16];
extern M2C_UNK D_80096384;
extern M2C_UNK D_800DD274[8];
extern M2C_UNK D_800DD294[8];

void func_800974DC(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    s32 temp_v1_2;
    u16 temp_v0;
    s32 temp_v0_4;
    u8 temp_v1;
    void *temp_a2;
    u8 *temp_v0_2;

    temp_v1 = ((S_800974DC_0 *)arg0)->unk_9B;
    if (temp_v1 >= 5U) {
        goto block_23;
    }
    (void)jt_keep; goto *D_80088B50[(u32)(temp_v1)];
jt_c0:
    func_800C77D0(arg3 - 0x20, arg1, 8, 0x300);
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = D_800DD294;
    func_8003DB94(arg2, *(M2C_UNK *)((u8 *)D_800DD294 + (((s32) (D_80083228 + ((S_800974DC_1 *)arg3)->unk_2A + 0x100) >> 7) & 0x1C)), 0);
    temp_v1_2 = ((u16) ((S_800974DC_1 *)arg3)->unk_2A >> 8) & 0xE;
    ((S_800974DC_2 *)arg1)->unk_0C = (s32) (*(s16 *)((u8 *)D_8006CCD8 + temp_v1_2) << 0x11);
    temp_v0_4 = *(s16 *)((u8 *)D_8006CCE8 + temp_v1_2);
    ((S_800974DC_2 *)arg1)->unk_14 = 0xFFEBC000;
    ((S_800974DC_2 *)arg1)->unk_10 = (s32) (temp_v0_4 << 0x11);
    ((S_800974DC_0 *)arg0)->unk_96.s = 3U;
    ((S_800974DC_0 *)arg0)->unk_98 = (u16) (((S_800974DC_0 *)arg0)->unk_98 & 0xFFF7);
    ((S_800974DC_0 *)arg0)->unk_9B = (u8) (((S_800974DC_0 *)arg0)->unk_9B + 1);
    return;
jt_c1:
    if (!(((S_800974DC_3 *)arg2)->unk_14 & 0x8000)) {
        goto block_5;
    }
    ((S_800974DC_0 *)arg0)->unk_96.s = 0U;
    goto block_6;
block_5:
    ((S_800974DC_0 *)arg0)->unk_96.s = (u16) (((S_800974DC_0 *)arg0)->unk_96.s - 1);
block_6:
    if (((S_800974DC_0 *)arg0)->unk_96.u != 0) {
        goto block_12;
    }
    if (((S_800974DC_0 *)arg0)->unk_102 != 0) {
        goto block_11;
    }
    ((S_800974DC_1 *)arg3)->unk_20 = 1;
    if (func_8009C12C(arg3, arg2, ((S_800974DC_1 *)arg3)->unk_2A, 1) != 0) {
        goto block_11;
    }
    temp_a2 = ((S_800974DC_1 *)arg3)->unk_60;
    if (temp_a2 == NULL) {
        goto block_11;
    }
    ((S_800974DC_1 *)arg3)->unk_60 = NULL;
    ((S_800974DC_4 *)temp_a2)->unk_1C = (s32) (((S_800974DC_4 *)temp_a2)->unk_1C & 0xEFFFFFFF);
    ((S_800974DC_6 *)(((S_800974DC_4_pre *)temp_a2)[-1].unk_00))->unk_0C = 0x808080;
block_11:
block_12:
    if ((s16) ((S_800974DC_0 *)arg0)->unk_96.s > 0) {
        goto block_15;
    }
    if (!(((S_800974DC_3 *)arg2)->unk_14 & 0xE000)) {
        goto block_15;
    }
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = D_800DD274;
    func_8003DB94(arg2, *(M2C_UNK *)((u8 *)D_800DD274 + (((s32) (D_80083228 + ((S_800974DC_1 *)arg3)->unk_2A + 0x100) >> 7) & 0x1C)), 0);
    ((S_800974DC_0 *)arg0)->unk_9B = (u8) (((S_800974DC_0 *)arg0)->unk_9B + 1);
jt_c2:
block_15:
    if (!(((S_800974DC_0 *)arg0)->unk_A2 & 0x10)) {
        goto block_23;
    }
    ((S_800974DC_2 *)arg1)->unk_14 = 0;
    ((S_800974DC_2 *)arg1)->unk_10 = 0;
    ((S_800974DC_2 *)arg1)->unk_0C = 0;
    if ((s16) ((S_800974DC_0 *)arg0)->unk_96.s > 0) {
        goto block_23;
    }
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = D_800DD274;
    func_8003DB94(arg2, *(M2C_UNK *)((u8 *)D_800DD274 + (((s32) (D_80083228 + ((S_800974DC_1 *)arg3)->unk_2A + 0x100) >> 7) & 0x1C)), 0);
    ((S_800974DC_0 *)arg0)->unk_9B = 3U;
    return;
jt_c3: {
    s32 coord;
    u32 delta;
    if (!(((S_800974DC_3 *)arg2)->unk_14 & 0xE000)) {
        goto block_23;
    }
    ((S_800974DC_2 *)arg1)->unk_14 = 0;
    ((S_800974DC_0 *)arg0)->unk_96.s = 2U;
    delta = (u32)((S_800974DC_3 *)arg2)->unk_24 << 6;
    coord = ((S_800974DC_2 *)arg1)->unk_02 - 0x20;
    delta -= (u32)coord;
    ((S_800974DC_2 *)arg1)->unk_0C = (s32)(delta * 0x10000U) / (s16) ((S_800974DC_0 *)arg0)->unk_96.s;
    coord = ((S_800974DC_2 *)arg1)->unk_06 - 0x20;
    delta = ((u32)((S_800974DC_3 *)arg2)->unk_25 << 6) - (u32)coord;
    ((S_800974DC_2 *)arg1)->unk_10 = (s32)(delta * 0x10000U) / (s16) ((S_800974DC_0 *)arg0)->unk_96.s;
    ((S_800974DC_0 *)arg0)->unk_9B = (u8) (((S_800974DC_0 *)arg0)->unk_9B + 1);
    return;
}
jt_c4:
    temp_v0 = ((S_800974DC_0 *)arg0)->unk_96.s - 1;
    ((S_800974DC_0 *)arg0)->unk_96.s = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        goto block_22;
    }
    if (!(((S_800974DC_3 *)arg2)->unk_14 & 0x8000)) {
        goto block_23;
    }
block_22:
    ((S_800974DC_2 *)arg1)->unk_14 = 0;
    ((S_800974DC_2 *)arg1)->unk_10 = 0;
    ((S_800974DC_2 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_800974DC_3 *)arg2)->unk_24, ((S_800974DC_3 *)arg2)->unk_25);
    func_80099F04(((S_800974DC_1 *)arg3)->unk_5C);
    temp_v0_2 = D_80083460;
    ((S_800974DC_5 *)temp_v0_2)->unk_02 = (u16) (((S_800974DC_5 *)temp_v0_2)->unk_02 | 0x412);
    ((S_800974DC_0 *)arg0)->unk_8C = &D_80096384;
    ((S_800974DC_5 *)temp_v0_2)->unk_0C = 0;
    ((S_800974DC_0 *)arg0)->unk_96.s = 0U;
block_23:
    return;
}
