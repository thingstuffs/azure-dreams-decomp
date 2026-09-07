#include "common.h"
#include "m2c_compat.h"

typedef struct Copy24 {
    s32 word0;
    s32 word4;
    s32 word8;
    s32 wordC;
    s32 word10;
    s32 word14;
} Copy24;

extern s32 D_800DEB70;
extern u8 D_80045340[];

void *func_8003FD64();
M2C_UNK func_8004491C();
s32 rand();
extern M2C_UNK D_80025094;

typedef struct S_80025270_0 {
    u8 pad_00[0x8];
    Copy24 * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80025270_0;   /* temp_v0 in func_80025270 */

typedef struct S_80025270_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x12];
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
} S_80025270_1;   /* temp_a0_2 in func_80025270 */

typedef struct S_80025270_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80025270_2;   /* arg0 in func_80025270 */

typedef struct S_80025270_3 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_80025270_3;   /* temp_v1 in func_80025270 */

s32 func_80025270(void *arg0, Copy24 *arg1, s16 arg2) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v1_2;
    s32 var_v0;
    S_80025270_1 *temp_a0_2;
    Copy24 *temp_v1;
    void *temp_v0;
    s16 arg2_hold;
    temp_v0 = func_8003FD64(0x212, (u8 *)arg0 - 0x20);
    if (temp_v0 != NULL) {
        arg2_hold = arg2;
        temp_a0_2 = temp_v0 + 0x20;
        ((S_80025270_0 *)temp_v0)->unk_10 = &D_80025094;
        ((S_80025270_0 *)temp_v0)->unk_20 = (s32)arg0;
        temp_a0_2->unk_08 = (s16) (arg2_hold * 7);
        temp_a0_2->unk_04 = 0;
        temp_a0_2->unk_06 = 0;
        temp_a0_2->unk_0A = 0;
        temp_a0_2->unk_0C = (s16) (arg2_hold * 0x600);
        temp_a0_2->unk_20 = arg1->wordC;
        temp_a0_2->unk_24 = arg1->word10;
        temp_a0_2->unk_28 = arg1->word14;
        arg0 = ((S_80025270_0 *)temp_v0)->unk_0C;
        ((S_80025270_2 *)arg0)->unk_0E = 0x20;
        ((S_80025270_2 *)arg0)->unk_0D = 0x20;
        ((S_80025270_2 *)arg0)->unk_0C = 0x20;
        ((S_80025270_2 *)arg0)->unk_12 = 0x7DCF;
        ((S_80025270_2 *)arg0)->unk_14 = (u16) (((S_80025270_2 *)arg0)->unk_14 | 0xC);
        ((S_80025270_2 *)arg0)->unk_10 = (u16) (((S_80025270_2 *)arg0)->unk_10 | 0x20);
        ((S_80025270_2 *)arg0)->unk_14 = (u16) (((S_80025270_2 *)arg0)->unk_14 | 0x100);
        func_8003DB94(arg0, &D_800DEB70, 0);
        var_v0 = rand();
        temp_v1_2 = var_v0;
        if (temp_v1_2 < 0) {
            var_v0 = temp_v1_2 + 0xFFF;
        }
        ((S_80025270_2 *)arg0)->unk_1A = (s16) (temp_v1_2 - ((var_v0 >> 0xC) << 0xC));
        ((S_80025270_2 *)arg0)->unk_1E = 0x400;
        ((S_80025270_2 *)arg0)->unk_1C = 0x400;
        func_8004491C(temp_v0, D_80045340);
        temp_v1 = ((S_80025270_0 *)temp_v0)->unk_08;
        *temp_v1 = *arg1;
        temp_a0 = ((S_80025270_3 *)temp_v1)->unk_00;
        temp_a1 = ((S_80025270_3 *)temp_v1)->unk_04;
        ((S_80025270_3 *)temp_v1)->unk_0C = temp_a0;
        ((S_80025270_3 *)temp_v1)->unk_10 = temp_a1;
        return (s32)temp_v0;
    }
    return 0;
}
