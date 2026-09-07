#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_8001659C_4 {
    void * unk_00;
} S_8001659C_4;   /* &D_80016000 in func_8001659C */

typedef struct S_8001659C_5 {
    u8 pad_00[0x1C];
    void * unk_1C;
    void * unk_20;
} S_8001659C_5;   /* ((S_8001659C_4 *)(&D_80016000))->unk_00 in func_8001659C */

typedef struct S_8001659C_6 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_8001659C_6;   /* (*(void **)((u8 *)(&D_80016000) + 0)) in func_8001659C */

typedef struct S_8001659C_7 {
    u8 pad_00[0x248];
    M2C_UNK (*unk_248)(M2C_UNK);
    u8 pad_24C[0xC];
    M2C_UNK (*unk_258)(M2C_UNK);
} S_8001659C_7;   /* ((S_8001659C_5 *)(((S_8001659C_4 *)(&D_80016000))->unk_00))->unk_20 in func_8001659C */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK D_80016000;

typedef struct S_8001659C_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_8001659C_0;   /* temp_v1 in func_8001659C */

typedef struct S_8001659C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8001659C_1;   /* temp_v1_2 in func_8001659C */

typedef struct S_8001659C_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x10];
    s32 unk_18;
} S_8001659C_2;   /* temp_v1_3 in func_8001659C */

typedef struct S_8001659C_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    s32 unk_1C;
} S_8001659C_3;   /* temp_v1_4 in func_8001659C */

void func_8001659C(void) {
    S_8001659C_0 *temp_v1;
    S_8001659C_1 *temp_v1_2;
    S_8001659C_2 *temp_v1_3;
    S_8001659C_3 *temp_v1_4;

    ((S_8001659C_7 *)(((S_8001659C_5 *)(((S_8001659C_4 *)(&D_80016000))->unk_00))->unk_20))->unk_248(0);
    temp_v1 = ((S_8001659C_6 *)((*(void **)((u8 *)(&D_80016000) + 0))))->unk_1C;
    temp_v1->unk_10 = (s32) temp_v1->unk_04;
    temp_v1_2 = ((S_8001659C_5 *)(((S_8001659C_4 *)(&D_80016000))->unk_00))->unk_1C;
    temp_v1_2->unk_14 = (s32) (temp_v1_2->unk_08 + 0x20);
    ((S_8001659C_7 *)(((S_8001659C_5 *)(((S_8001659C_4 *)(&D_80016000))->unk_00))->unk_20))->unk_258(0xD);
    temp_v1_3 = ((S_8001659C_6 *)((*(void **)((u8 *)(&D_80016000) + 0))))->unk_1C;
    temp_v1_3->unk_18 = (s32) temp_v1_3->unk_04;
    temp_v1_4 = ((S_8001659C_5 *)(((S_8001659C_4 *)(&D_80016000))->unk_00))->unk_1C;
    temp_v1_4->unk_1C = (s32) temp_v1_4->unk_08;
}
