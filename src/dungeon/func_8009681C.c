#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009BF7C_2 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8009BF7C_2;   /* temp_v0 in func_8009BF7C */

typedef struct S_8009BF7C_3 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_8009BF7C_3;   /* ((S_8009BF7C_2 *)temp_v0)->unk_0C in func_8009BF7C */




void *func_8003FD64();                  /* extern */
extern M2C_UNK D_8009BE2C;
extern s32 D_800E3D7C;

typedef struct S_8009BF7C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
} S_8009BF7C_0;   /* temp_v0 in func_8009BF7C */

typedef struct S_8009BF7C_1 {
    u8 pad_00[0x5];
    s8 unk_05;
    s16 unk_06;
} S_8009BF7C_1;   /* temp_a0 in func_8009BF7C */

void func_8009BF7C(s32 arg0, s8 arg1) {
    S_8009BF7C_1 *temp_a0;
    S_8009BF7C_0 *temp_v0;

    temp_v0 = func_8003FD64(0x212, D_800E3D7C - 0x20);
    if (temp_v0 != NULL) {
        temp_a0 = temp_v0->unk_0C;
        temp_v0->unk_10 = &D_8009BE2C;
        temp_a0->unk_05 = arg1;
        temp_a0->unk_06 = (s16) arg1;
        ((S_8009BF7C_3 *)(((S_8009BF7C_2 *)temp_v0)->unk_0C))->unk_04 = (s8) ((arg0 << 0x10) != 0);
    }
}
