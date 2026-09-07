#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800B8CF0;
extern M2C_UNK D_800DF358;

typedef struct S_800B8D64_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
} S_800B8D64_0;   /* temp_v0 in func_800B8D64 */

typedef struct S_800B8D64_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800B8D64_1;   /* temp_v0_2 in func_800B8D64 */

typedef struct S_800B8D64_2 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800B8D64_2;   /* temp_v1 in func_800B8D64 */

void func_800B8D64(s16 arg0, s16 arg1, s16 arg2) {
    S_800B8D64_0 *temp_v0;
    S_800B8D64_1 *temp_v0_2;
    S_800B8D64_2 *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = &D_800B8CF0;
        func_8004491C(temp_v0, &D_80045340);
        temp_v0_2 = temp_v0->unk_08;
        temp_v0_2->unk_02 = arg0;
        temp_v0_2->unk_06 = arg1;
        temp_v0_2->unk_0A = arg2;
        temp_v1 = temp_v0->unk_0C;
        temp_v1->unk_08 = &D_800DF358;
        temp_v1->unk_1E = 0x800;
        temp_v1->unk_1C = 0x800;
        temp_v1->unk_14 = (u16) (temp_v1->unk_14 | 0xC);
        temp_v0->unk_22 = 6;
    }
}
