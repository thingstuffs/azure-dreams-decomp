#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();                  /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800F7348;
extern M2C_UNK D_800FBE24;

typedef struct S_807AFC9C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_807AFC9C_0;   /* temp_v0 in func_807AFC9C */

typedef struct S_807AFC9C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_807AFC9C_1;   /* temp_s0 in func_807AFC9C */

typedef struct S_807AFC9C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_807AFC9C_2;   /* arg1 in func_807AFC9C */

typedef struct S_807AFC9C_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    M2C_UNK * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_807AFC9C_3;   /* temp_a0 in func_807AFC9C */

typedef struct S_807AFC9C_4 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_807AFC9C_4;   /* arg2 in func_807AFC9C */

typedef struct S_807AFC9C_5 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x4];
    s16 unk_0C;
} S_807AFC9C_5;   /* temp_v1 in func_807AFC9C */

void func_807AFC9C(s32 arg0, S_807AFC9C_2 *arg1, S_807AFC9C_4 *arg2) {
    S_807AFC9C_3 *temp_a0;
    S_807AFC9C_1 *temp_s0;
    void *temp_v0;
    S_807AFC9C_5 *temp_v1;

    temp_v0 = func_8003FD64(0x212, arg0);
    if (temp_v0 != NULL) {
        ((S_807AFC9C_0 *)temp_v0)->unk_10 = &D_800F7348;
        func_8004491C(temp_v0, &D_80045340);
        temp_s0 = ((S_807AFC9C_0 *)temp_v0)->unk_08;
        temp_s0->unk_02 = (s16) ((arg1->unk_02 + (rand() & 0x3F)) - 0x20);
        temp_s0->unk_06 = (s16) ((arg1->unk_06 + (rand() & 0x3F)) - 0x20);
        temp_s0->unk_0A = (s16) ((arg1->unk_0A + (rand() & 0x3F)) - 0x20);
        temp_a0 = ((S_807AFC9C_0 *)temp_v0)->unk_0C;
        temp_a0->unk_08 = &D_800FBE24;
        if (arg2->unk_14 & 1) {
            temp_a0->unk_0C = 0x20;
        }
        if (arg2->unk_14 & 2) {
            temp_a0->unk_0E = 0x20;
        }
        if (arg2->unk_14 & 4) {
            temp_a0->unk_0D = 0x20;
        }
        temp_a0->unk_1E = 0x1000;
        temp_a0->unk_1C = 0x1000;
        temp_a0->unk_06 = 8;
        temp_v1 = temp_v0 + 0x20;
        temp_a0->unk_14 = (u16) (temp_a0->unk_14 | 0xC);
        temp_v1->unk_0C = 0x10;
        ((S_807AFC9C_0 *)temp_v0)->unk_20 = arg2;
        temp_v1->unk_04 = arg1;
    }
}
