#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s16 rand();                                /* extern */
extern M2C_UNK D_80025D28;
extern M2C_UNK D_80027460;
extern M2C_UNK D_800CEEFC;

typedef struct S_80025FCC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80025FCC_0;   /* temp_v0 in func_80025FCC */

typedef struct S_80025FCC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_80025FCC_1;   /* temp_v0_2 in func_80025FCC */

typedef struct S_80025FCC_2 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0x1];
    s8 unk_0D;
    u8 pad_0E[0x2];
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80025FCC_2;   /* temp_v1 in func_80025FCC */

typedef struct S_80025FCC_3 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    u8 pad_22[0xE];
    s16 unk_30;
    u8 pad_32[0x4];
    s16 unk_36;
    s16 unk_38;
    u8 pad_3A[0x4];
    s16 unk_3E;
    s16 unk_40;
} S_80025FCC_3;   /* temp_s0 in func_80025FCC */

void *func_80025FCC(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    S_80025FCC_3 *temp_s0;
    void *temp_v0;
    S_80025FCC_1 *temp_v0_2;
    S_80025FCC_2 *temp_v1;

    temp_v0 = func_8003FC64(0x202);
    if (temp_v0 != NULL) {
        ((S_80025FCC_0 *)temp_v0)->unk_10 = &D_80025D28;
        func_8004491C(temp_v0, &D_800CEEFC);
        temp_v0_2 = ((S_80025FCC_0 *)temp_v0)->unk_08;
        temp_s0 = temp_v0 + 0x20;
        temp_v0_2->unk_0E = arg0;
        temp_v0_2->unk_02 = arg0;
        temp_v0_2->unk_12 = arg1;
        temp_v0_2->unk_06 = arg1;
        temp_v0_2->unk_16 = arg2;
        temp_v0_2->unk_0A = arg2;
        temp_v1 = ((S_80025FCC_0 *)temp_v0)->unk_0C;
        temp_v1->unk_1E = 0x200;
        temp_v1->unk_1C = 0x200;
        temp_v1->unk_0D = 0x20;
        temp_v1->unk_14 = 0xC;
        temp_v1->unk_08 = &D_80027460;
        temp_v1->unk_10 = 0x20;
        temp_s0->unk_30 = 0x20;
        temp_s0->unk_3E = 0x10;
        temp_s0->unk_36 = arg3;
        temp_s0->unk_40 = 0x18;
        temp_s0->unk_38 = rand();
        temp_s0->unk_1C = arg0;
        temp_s0->unk_1E = arg1;
        temp_s0->unk_20 = arg2;
    }
    return temp_v0;
}
