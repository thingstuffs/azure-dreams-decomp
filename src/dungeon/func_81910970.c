#include "common.h"

typedef struct S_80024170_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80024170_0;   /* temp_v0 in func_80024170 */

typedef struct S_80024170_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u16 unk_08;
    u8 pad_0A[0x2];
    s32 unk_0C;
} S_80024170_1;   /* temp_s2 in func_80024170 */

typedef struct S_80024170_2 {
    u8 pad_00[0x12];
    u16 unk_12;
} S_80024170_2;   /* arg0 in func_80024170 */

typedef struct S_80024170_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80024170_3;   /* temp_s0 in func_80024170 */

typedef struct S_80024170_4 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80024170_4;   /* temp_v0_2 in func_80024170 */



typedef struct {
    s32 f0;
    s32 f1;
    s32 f2;
    s32 f3;
    s32 f4;
    s32 f5;
} Copy6;

extern void *func_8003FC64(s32);
extern s32 func_8004491C(void *, void *);
extern s32 rand(void);
extern u8 D_80024044[9];
extern u8 D_80045340[9];
extern u8 D_800DE720[9];

s32 func_80024170(S_80024170_2 *arg0, void *arg1)
{
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_v1;
    s32 var_v0;
    S_80024170_3 *temp_s0;
    S_80024170_1 *temp_s2;
    void *temp_v0;
    S_80024170_4 *temp_v0_2;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_s2 = temp_v0 + 0x20;
        ((S_80024170_0 *)temp_v0)->unk_10 = D_80024044;
        ((S_80024170_0 *)temp_v0)->unk_20 = arg0;
        temp_s2->unk_06 = 0;
        temp_s2->unk_08 = arg0->unk_12;
        temp_s0 = ((S_80024170_0 *)temp_v0)->unk_0C;
        temp_s0->unk_0E = 0x80;
        temp_s0->unk_0D = 0x80;
        temp_s0->unk_0C = 0x80;
        temp_s0->unk_08 = D_800DE720;
        temp_s0->unk_12 = 0x7E00;
        temp_s0->unk_14 |= 0x100;
        var_v0 = rand();
        temp_v1 = var_v0;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        temp_s0->unk_1A = temp_v1 - ((var_v0 >> 0xC) << 0xC);
        temp_s0->unk_1E = 0x400;
        temp_s0->unk_1C = 0x400;
        func_8004491C(temp_v0, D_80045340);
        temp_v0_2 = ((S_80024170_0 *)temp_v0)->unk_08;
        *(Copy6 *)temp_v0_2 = *(Copy6 *)arg1;
        temp_v1 = temp_v0_2->unk_08;
        temp_s2->unk_0C = temp_v1;
        return (s32)temp_v0;
    }
    return 0;
}
