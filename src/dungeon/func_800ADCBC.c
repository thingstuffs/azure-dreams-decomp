#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();                  /* extern */
extern M2C_UNK D_800B328C;

typedef struct S_800B341C_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800B341C_0;   /* temp_v0 in func_800B341C */

typedef struct S_800B341C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x86];
    s16 unk_8E;
} S_800B341C_1;   /* temp_v0_2 in func_800B341C */

void func_800B341C(s32 arg0, s32 arg1, s16 arg2) {
    void *temp_v0;
    S_800B341C_1 *temp_v0_2;

    if (arg1 != 0) {
        temp_v0 = func_8003FD64(0x210, arg0);
        if (temp_v0 != NULL) {
            ((S_800B341C_0 *)temp_v0)->unk_10 = &D_800B328C;
            temp_v0_2 = temp_v0 + 0x20;
            ((S_800B341C_0 *)temp_v0)->unk_20 = arg0;
            temp_v0_2->unk_04 = arg1;
            temp_v0_2->unk_8E = arg2;
        }
    }
}
