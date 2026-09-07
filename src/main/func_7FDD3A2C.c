#include "common.h"
#include "m2c_compat.h"

typedef struct S_7FDD3A2C_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_7FDD3A2C_3;   /* temp_v0 in func_7FDD3A2C */

typedef struct S_7FDD3A2C_4 {
    s32 unk_00;
    s32 unk_04;
} S_7FDD3A2C_4;   /* ((S_7FDD3A2C_3 *)temp_v0)->unk_08 in func_7FDD3A2C */




void *func_7003FC64();                       /* extern */
M2C_UNK func_7004491C();           /* extern */
extern M2C_UNK D_80044BB0;

typedef struct S_7FDD3A2C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_7FDD3A2C_0;   /* temp_v0 in func_7FDD3A2C */

typedef struct S_7FDD3A2C_1 {
    s32 unk_00;
    s32 unk_04;
} S_7FDD3A2C_1;   /* arg0 in func_7FDD3A2C */

typedef struct S_7FDD3A2C_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_7FDD3A2C_2;   /* temp_v0_2 in func_7FDD3A2C */

void *func_7FDD3A2C(S_7FDD3A2C_1 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    S_7FDD3A2C_0 *temp_v0;
    S_7FDD3A2C_2 *temp_v0_2;

    temp_v0 = func_7003FC64(0x136);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = arg1;
        ((S_7FDD3A2C_4 *)(((S_7FDD3A2C_3 *)temp_v0)->unk_08))->unk_00 = (s32) arg0->unk_00;
        ((S_7FDD3A2C_4 *)(((S_7FDD3A2C_3 *)temp_v0)->unk_08))->unk_04 = (s32) arg0->unk_04;
        func_7004491C(temp_v0, &D_80044BB0);
        temp_v0_2 = temp_v0->unk_0C;
        temp_v0_2->unk_1E = 0x1000;
        temp_v0_2->unk_1C = 0x1000;
        temp_v0_2->unk_08 = arg2;
        temp_v0_2->unk_0C = 0x808080;
        temp_v0->unk_20 = arg3;
    }
    return temp_v0;
}
