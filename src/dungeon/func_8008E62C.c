#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();                  /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80048A44(); /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80093A94;

typedef struct S_80093D8C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x2];
    s16 unk_26;
} S_80093D8C_0;   /* temp_v0 in func_80093D8C */

typedef struct S_80093D8C_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80093D8C_1;   /* temp_v1 in func_80093D8C */

typedef struct S_80093D8C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80093D8C_2;   /* arg1 in func_80093D8C */

typedef struct S_80093D8C_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80093D8C_3;   /* temp_a0 in func_80093D8C */

typedef struct S_80093D8C_4 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_80093D8C_4;   /* arg2 in func_80093D8C */

void func_80093D8C(s32 arg0, S_80093D8C_2 *arg1, S_80093D8C_4 *arg2) {
    S_80093D8C_3 *temp_a0;
    S_80093D8C_0 *temp_v0;
    S_80093D8C_1 *temp_v1;

    temp_v0 = func_8003FD64(0x310, arg0 - 0x20);
    if (temp_v0 != NULL) {
        temp_v1 = temp_v0->unk_08;
        temp_v0->unk_10 = &D_80093A94;
        temp_v1->unk_02 = (u16) arg1->unk_02;
        temp_v1->unk_06 = (u16) arg1->unk_06;
        temp_v1->unk_0A = (u16) arg1->unk_0A;
        temp_a0 = temp_v0->unk_0C;
        temp_a0->unk_28 = (s32) arg2->unk_28;
        temp_a0->unk_1E = 0x1000;
        temp_a0->unk_14 = 0xCU;
        temp_a0->unk_10 = 0x20;
        temp_a0->unk_0C = 0xF8F8F8;
        temp_a0->unk_1C = 0;
        temp_a0->unk_06 = 4;
        temp_a0->unk_14 = (u16) (temp_a0->unk_14 | 0x200);
        func_80048A44(temp_a0, 0xD0, 0, 2);
        func_8004491C(temp_v0, &D_80045340);
        temp_v0->unk_20 = arg2;
        temp_v0->unk_26 = 0x10;
    }
}
