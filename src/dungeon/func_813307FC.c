#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

typedef struct {
    s32 words[8];
} __attribute__((packed)) LocalTable;

extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern M2C_UNK D_80045340;
extern u8 D_800DEAE0[];
extern LocalTable D_8016482C;
extern M2C_UNK D_80167540[3];
extern s32 D_80175D50;


typedef struct S_801677FC_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801677FC_0;   /* (void *)D_80175D50 in func_801677FC */

typedef struct S_801677FC_1 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
} S_801677FC_1;   /* temp_v1 in func_801677FC */

typedef struct S_801677FC_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_801677FC_2;   /* temp_v0 in func_801677FC */

typedef struct S_801677FC_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_801677FC_3;   /* temp_a0 in func_801677FC */

typedef struct S_801677FC_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_801677FC_4;   /* temp_a0_2 in func_801677FC */

typedef struct S_801677FC_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801677FC_5;   /* temp_s2 in func_801677FC */

typedef struct S_801677FC_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_801677FC_6;   /* temp_s3 in func_801677FC */

typedef struct S_801677FC_7 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_801677FC_7;   /* temp_a0_3 in func_801677FC */

void func_801677FC(void)
{
    LocalTable table;
    s32 temp_v1_2;
    s32 var_s1;
    u8 *pb;
    S_801677FC_3 *temp_a0;
    S_801677FC_4 *temp_a0_2;
    S_801677FC_7 *temp_a0_3;
    S_801677FC_5 *temp_s2;
    S_801677FC_6 *temp_s3;
    void *temp_v0;
    S_801677FC_1 *temp_v1;

    table = D_8016482C;
    var_s1 = 0;
    temp_s3 = (void *)D_80175D50 + 0x20;
    temp_s2 = ((S_801677FC_0 *)((void *)D_80175D50))->unk_08;
    do {
        temp_v0 = func_8003FC64(0x212);
        if (temp_v0 != NULL) {
            temp_v1 = temp_v0 + 0x20;
            temp_v1->unk_18 = 0xE;
            temp_v1->unk_1A = 0xE;
            ((S_801677FC_2 *)temp_v0)->unk_10 = D_80167540;
            func_8004491C(temp_v0, &D_80045340);
            temp_a0 = ((S_801677FC_2 *)temp_v0)->unk_0C;
            temp_a0->unk_10 = 0x60;
            temp_a0->unk_14 =
                (u16)(temp_a0->unk_14 | 0xC);
            temp_a0_2 = ((S_801677FC_2 *)temp_v0)->unk_08;
            temp_a0_2->unk_00.at00.v = temp_s2->unk_00;
            temp_a0_2->unk_04.at00.v = temp_s2->unk_04;
            temp_a0_2->unk_08 =
                temp_s2->unk_08 + (s32)0xFFCE0000;
            temp_a0_2->unk_00.at02.v =
                (u16)(temp_a0_2->unk_00.at02.v +
                ((*(s16 *)((u8 *)(&table) + ((temp_s3->unk_2A >> 7) & 0x1C))) * 0x14));
            temp_v1_2 = var_s1 << 9;
            pb = (u8 *)&table + ((temp_s3->unk_2A >> 7) & 0x1C);
            temp_a0_2->unk_04.at02.v =
                (u16)(temp_a0_2->unk_04.at02.v +
                ((s16)*(u16 *)(pb + 2) * 0x14));
            temp_a0_3 = ((S_801677FC_2 *)temp_v0)->unk_0C;
            temp_a0_3->unk_1C = (s16)(temp_v1_2 + 0x1C00);
            temp_a0_3->unk_1E = (s16)(temp_v1_2 + 0x1400);
            temp_a0_3->unk_0E = 0;
            temp_a0_3->unk_0D = 0;
            temp_a0_3->unk_0C = 0;
            temp_a0_3->unk_06 = 0;
            temp_a0_3->unk_12 = 0x7DCF;
            temp_a0_3->unk_14 =
                (u16)(temp_a0_3->unk_14 | 0x100);
            func_8003DB94(temp_a0_3, D_800DEAE0, 0);
        }
        var_s1 += 1;
    } while (var_s1 < 0x10);
}
