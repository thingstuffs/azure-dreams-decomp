#include "common.h"
#include "m2c_compat.h"

extern s16 D_80083780[];
extern u8 D_80083498[];
extern u8 D_800DF334[];
M2C_UNK func_80024654();
void *func_8003FD64();
s32 func_800644B8();
s32 func_80064584();
s16 func_800A07D0();
M2C_UNK func_800B835C();
extern M2C_UNK D_80028214;
extern M2C_UNK D_80024728;

typedef struct S_80024ED4_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024ED4_0;   /* arg0 in func_80024ED4 */

typedef struct S_80024ED4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80024ED4_1;   /* temp_v0 in func_80024ED4 */

typedef struct S_80024ED4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_80024ED4_2;   /* temp_s0 in func_80024ED4 */

typedef struct S_80024ED4_3 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} S_80024ED4_3;   /* temp_v1 in func_80024ED4 */

typedef struct S_80024ED4_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x16];
    s16 unk_30;
    u8 pad_32[0x6];
    s16 unk_38;
} S_80024ED4_4;   /* temp_s1 in func_80024ED4 */

void *func_80024ED4(S_80024ED4_0 *arg0) {
    s32 sp20[2];
    s32 var_s3;
    M2C_UNK var_a0;
    s16 temp_s6;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u8 *var_a1;
    S_80024ED4_2 *temp_s0;
    S_80024ED4_4 *temp_s1;
    void *temp_v0;
    S_80024ED4_3 *temp_v1;
    void *var_s4;
    s16 *temp_v0_1;

    temp_v0_1 = D_80083780;
    var_s4 = NULL;
    var_s3 = 0;
    temp_s6 = func_800A07D0(temp_v0_1[1], temp_v0_1[3], arg0->unk_02, arg0->unk_06);
    do {
        var_a0 = 0x12;
        if (var_s3 != 0) {
            var_a0 = 0x212;
        }
        var_a1 = var_s4;
        if (var_s4 == NULL) {
            var_a1 = D_80083498;
        }
        temp_v0 = func_8003FD64(var_a0, var_a1);
        temp_s1 = temp_v0 + 0x20;
        if (temp_v0 != NULL) {
            temp_s0 = ((S_80024ED4_1 *)temp_v0)->unk_08;
            ((S_80024ED4_1 *)temp_v0)->unk_10 = &D_80024728;
            temp_v0_2 = (u16) arg0->unk_02;
            temp_s0->unk_02 = temp_v0_2;
            temp_s0->unk_0E = temp_v0_2;
            temp_v0_3 = (u16) arg0->unk_06;
            temp_s0->unk_06 = temp_v0_3;
            temp_s0->unk_12 = temp_v0_3;
            temp_v0_4 = arg0->unk_0A;
            temp_s0->unk_0A = temp_v0_4;
            temp_s0->unk_16 = temp_v0_4;
            temp_v1 = ((S_80024ED4_1 *)temp_v0)->unk_0C;
            temp_v1->unk_08 = &D_80028214;
            temp_v1->unk_1E = 0x800;
            temp_v1->unk_1C = 0x800;
            temp_s1->unk_30 = 0x10;
            if (var_s3 == 0) {
                temp_s1->unk_14 = (s16) (temp_s0->unk_02 + (func_80064584(temp_s6) >> 5));
                temp_s1->unk_16 = (s16) (temp_s0->unk_06 + (func_800644B8(temp_s6) >> 5));
                temp_s1->unk_18 = (s16) (temp_s0->unk_0A - 0x40);
                func_80024654((s16) temp_s0->unk_02, (s16) temp_s0->unk_06, (s16) temp_s0->unk_0A, temp_s1->unk_14, (s32) temp_s1->unk_16, (s32) temp_s1->unk_18, temp_v0 + 0x2C);
                sp20[0] = 0x01200340;
                sp20[1] = 0x200020;
                func_800B835C(D_800DF334, sp20, 1, 0);
            }
            temp_s1->unk_08 = var_s4;
            var_s4 = temp_v0;
            temp_s1->unk_38 = var_s3;
        } else {
            return var_s4;
        }
        var_s3++;
    } while (var_s3 < 0x10);
    return temp_v0;
}
