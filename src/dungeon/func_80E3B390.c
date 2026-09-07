#include "common.h"
#include "m2c_compat.h"

typedef struct S_80174B90_4 {
    u8 pad_00[0x14];
    void * unk_14;
} S_80174B90_4;   /* temp_s0 in func_80174B90 */

typedef struct S_80174B90_5 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80174B90_5;   /* temp_v0 in func_80174B90 */

typedef struct S_80174B90_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80174B90_6;   /* arg0 in func_80174B90 */

typedef struct S_80174B90_7 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x14];
    s32 unk_28;
} S_80174B90_7;   /* ((S_80174B90_4 *)temp_s0)->unk_14 in func_80174B90 */

typedef struct S_80174B90_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174B90_8;   /* ((S_80174B90_5 *)temp_v0)->unk_08 in func_80174B90 */

typedef struct S_80174B90_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174B90_9;   /* ((S_80174B90_6 *)arg0)->unk_08 in func_80174B90 */




void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80047784();    /* extern */
extern M2C_UNK D_8017474C;
extern M2C_UNK D_80175540;

typedef struct S_80174B90_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80174B90_0;   /* temp_v0 in func_80174B90 */

typedef struct S_80174B90_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    void * unk_0C;
    u8 pad_10[0x4];
    void * unk_14;
    void * unk_18;
    s16 unk_1C;
} S_80174B90_1;   /* temp_s0 in func_80174B90 */

typedef struct S_80174B90_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80174B90_2;   /* arg0 in func_80174B90 */

typedef struct S_80174B90_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x8];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80174B90_3;   /* temp_a0 in func_80174B90 */

void func_80174B90(S_80174B90_2 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    S_80174B90_3 *temp_a0;
    S_80174B90_1 *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x100, arg0);
    if (temp_v0 != NULL) {
        temp_a0 = ((S_80174B90_0 *)temp_v0)->unk_0C;
        temp_s0 = temp_v0 + 0x20;
        ((S_80174B90_0 *)temp_v0)->unk_10 = &D_8017474C;
        temp_s0->unk_14 = (void *) arg0->unk_0C;
        temp_s0->unk_18 = (void *) arg0->unk_08;
        temp_a0->unk_1E = 0x1000;
        temp_a0->unk_1C = 0x1000;
        temp_a0->unk_0C = 0x808080;
        temp_a0->unk_28 = (s32) ((S_80174B90_7 *)(((S_80174B90_4 *)temp_s0)->unk_14))->unk_28;
        temp_a0->unk_12 = (u16) ((S_80174B90_7 *)(((S_80174B90_4 *)temp_s0)->unk_14))->unk_12;
        ((S_80174B90_8 *)(((S_80174B90_5 *)temp_v0)->unk_08))->unk_02 = (u16) ((S_80174B90_9 *)(((S_80174B90_6 *)arg0)->unk_08))->unk_02;
        ((S_80174B90_8 *)(((S_80174B90_5 *)temp_v0)->unk_08))->unk_06 = (u16) ((S_80174B90_9 *)(((S_80174B90_6 *)arg0)->unk_08))->unk_06;
        ((S_80174B90_8 *)(((S_80174B90_5 *)temp_v0)->unk_08))->unk_0A = (u16) ((S_80174B90_9 *)(((S_80174B90_6 *)arg0)->unk_08))->unk_0A;
        func_80047784(temp_a0, 0x46, 0);
        func_8004491C(temp_v0, &D_80175540);
        ((S_80174B90_0 *)temp_v0)->unk_20 = arg1;
        temp_s0->unk_04 = arg2;
        temp_s0->unk_08 = arg3;
        temp_s0->unk_0C = arg0;
        temp_s0->unk_1C = 0x1000;
    }
}
