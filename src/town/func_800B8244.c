#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B59A4_3 {
    u8 pad_00[0x30];
    void * unk_30;
} S_800B59A4_3;   /* var_s1 in func_800B59A4 */

typedef struct S_800B59A4_4 {
    s32 unk_00;
    void * unk_04;
} S_800B59A4_4;   /* ((S_800B59A4_3 *)var_s1)->unk_30 in func_800B59A4 */

typedef struct S_800B59A4_5 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800B59A4_5;   /* ((S_800B59A4_4 *)(((S_800B59A4_3 *)var_s1)->unk_30))->unk_04 in func_800B59A4 */




s32 func_8004A658();
s32 func_8004AC3C();
M2C_UNK bzero(void **, M2C_UNK);
M2C_UNK func_800B5264();
M2C_UNK func_800B53BC();
M2C_UNK func_800B58B8(void **, s32);
s32 func_800B5918();

typedef struct S_800B59A4_0 {
    u8 pad_00[0x18];
    s32 unk_18;
    u8 pad_1C[0x8];
    s32 unk_24;
} S_800B59A4_0;   /* var_s1 in func_800B59A4 */

typedef struct S_800B59A4_1 {
    u8 unk_00;
    u8 unk_01;
} S_800B59A4_1;   /* temp_v0 in func_800B59A4 */

typedef struct S_800B59A4_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800B59A4_2;   /* temp_v0_2 in func_800B59A4 */

void func_800B59A4(s32 arg0, void *arg1) {
    s32 sp18[10];
    s16 var_s4;
    s32 var_s2;
    s32 var_s3;
    void **temp_s0;
    void *temp_a0;
    S_800B59A4_1 *temp_v0;
    S_800B59A4_2 *temp_v0_2;
    void *var_s1;

    var_s1 = arg1;
    bzero((void **) &sp18[0], 0xC);
    func_800B58B8((void **) &sp18[0], arg0);
    var_s3 = 0;
    var_s4 = 0x66;
    var_s2 = 0xD8;
loop_1:
    temp_s0 = (void **)((s32)(var_s3 << 2) + (s32)&sp18[0]);
    temp_a0 = *temp_s0;
    if (temp_a0 != NULL) {
        func_800B5264(((S_800B59A4_0 *)var_s1)->unk_18, func_8004AC3C(temp_a0, &sp18[8]), sp18[8], 0x58, var_s2);
        func_800B53BC(((S_800B59A4_0 *)var_s1)->unk_24, func_800B5918(*temp_s0, &sp18[4]), 0, 0xA0, var_s2);
        temp_v0 = *temp_s0;
        var_s3 += 1;
        ((S_800B59A4_4 *)(((S_800B59A4_3 *)var_s1)->unk_30))->unk_00 = func_8004A658(temp_v0->unk_01, temp_v0->unk_00);
        ((S_800B59A4_5 *)(((S_800B59A4_4 *)(((S_800B59A4_3 *)var_s1)->unk_30))->unk_04))->unk_08 = -0x30;
        var_s2 += 0x10;
        temp_v0_2 = ((S_800B59A4_4 *)(((S_800B59A4_3 *)var_s1)->unk_30))->unk_04;
        var_s1 += 4;
        temp_v0_2->unk_0A = var_s4;
        var_s4 += 0x10;
        if (var_s3 < 3) {
            goto loop_1;
        }
    }
}
