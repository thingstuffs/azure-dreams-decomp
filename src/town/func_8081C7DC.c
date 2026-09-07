#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800267DC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800267DC_0;   /* temp_v0 in func_800267DC */

typedef struct S_800267DC_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_800267DC_1;   /* temp_s1 in func_800267DC */

typedef struct S_800267DC_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_800267DC_2;   /* arg0 in func_800267DC */

typedef struct S_800267DC_3 {
    void * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800267DC_3;   /* temp_s0 in func_800267DC */

typedef struct S_800267DC_4 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800267DC_4;   /* D_800F1564 in func_800267DC */



void *func_8003FC64();
void func_8004491C();
s32 rand();

extern u8 D_800268DC[];
extern u8 D_80045340[];
extern u8 D_800F1564[];

void func_800267DC(S_800267DC_2 *arg0) {
    S_800267DC_3 *temp_s0;
    S_800267DC_1 *temp_s1;
    S_800267DC_0 *temp_v0;

    temp_v0 = func_8003FC64(0x136);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = D_800268DC;
        func_8004491C(temp_v0, D_80045340);
        temp_s1 = temp_v0->unk_08;
        temp_s0 = temp_v0->unk_0C;
        temp_s1->unk_00 = arg0->unk_00 + 0xFFF90000;
        temp_s1->unk_04 = arg0->unk_04 + 0xFFFD0000;
        temp_s1->unk_08 = arg0->unk_08;
        temp_s1->unk_0C = arg0->unk_0C >> 1;
        temp_s1->unk_14 = ((rand() & 0x1FF) - 0x100) << 10;
        temp_s0->unk_1E = 0x800;
        temp_s0->unk_1C = 0x800;
        temp_s0->unk_10 = 0x60;
        temp_s0->unk_00 = D_800F1564;
        temp_s0->unk_14 |= 0xD;
        temp_s0->unk_08 = ((S_800267DC_4 *)D_800F1564)->unk_04;
        temp_s0->unk_04 = 0;
        temp_s0->unk_05 = 0;
        temp_s0->unk_0C = 0x8080F0;
    }
}
