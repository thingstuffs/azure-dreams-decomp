#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D5294_5 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800D5294_5;   /* temp_a0 in func_800D5294 */

typedef struct S_800D5294_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D5294_6;   /* ((S_800D5294_5 *)temp_a0)->unk_08 in func_800D5294 */


typedef struct S_800D5294_0_pre {
    u16 unk_00;
} S_800D5294_0_pre;   /* the 0x2 bytes before arg0 in func_800D5294, addressed as arg0[-1] */

typedef struct S_800D5294_0 {
    u8 pad_00[0x16];
    u16 unk_16;
    u8 pad_18[0x6];
    u16 unk_1E;
    u8 pad_20[0x4];
    void * unk_24;
    u8 pad_28[0x14];
    u16 unk_3C;
    u16 unk_3E;
    u16 unk_40;
} S_800D5294_0;   /* arg0 in func_800D5294 */

typedef struct S_800D5294_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D5294_1;   /* arg1 in func_800D5294 */

typedef struct S_800D5294_2 {
    u8 pad_00[0x1E];
    s16 unk_1E;
    s16 unk_20;
} S_800D5294_2;   /* temp_v0_3 in func_800D5294 */

typedef struct S_800D5294_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
} S_800D5294_3;   /* temp_v0_2 in func_800D5294 */

typedef struct S_800D5294_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800D5294_4;   /* temp_s0 in func_800D5294 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800814A0[3];
extern u16 D_80083460[];
void *func_8003FC64();                       /* extern */
s32 rand();                                /* extern */
M2C_UNK func_800D4BD4(); /* extern */
extern M2C_UNK D_800D50FC[3];

void func_800D5294(void *arg0, S_800D5294_1 *arg1, M2C_UNK arg2) {
    s32 var_s1;
    u16 temp_v0;
    u16 temp_v0_4;
    s16 temp_v1;
    s16 temp_s3;
    S_800D5294_5 *temp_a0;
    S_800D5294_4 *temp_s0;
    u16 *fixed;
    M2C_UNK *temp_s5;
    void *temp_v0_2;
    S_800D5294_2 *temp_v0_3;

    temp_a0 = ((S_800D5294_0 *)arg0)->unk_24;
    arg1->unk_02 = (s16) (((S_800D5294_6 *)(temp_a0->unk_08))->unk_02 + ((S_800D5294_0 *)arg0)->unk_3C);
    arg1->unk_06 = (s16) (((S_800D5294_6 *)(temp_a0->unk_08))->unk_06 + ((S_800D5294_0 *)arg0)->unk_3E);
    arg1->unk_0A = (s16) (((S_800D5294_6 *)(temp_a0->unk_08))->unk_0A + ((S_800D5294_0 *)arg0)->unk_40);
    temp_v0 = ((S_800D5294_0 *)arg0)->unk_16 + 1;
    ((S_800D5294_0 *)arg0)->unk_16 = temp_v0;
    if ((s16) temp_v0 < 0x14) {
        var_s1 = 0;
        temp_s3 = 0x20;
        temp_s5 = D_800D50FC;
        do {
            temp_v0_2 = func_8003FC64(0x212);
            if (temp_v0_2 != NULL) {
                func_800D4BD4(temp_v0_2, arg0, arg1, arg2);
                temp_v0_3 = temp_v0_2 + 0x20;
                temp_v0_3->unk_1E = temp_s3;
                temp_v0_3->unk_20 = temp_s3;
                ((S_800D5294_3 *)temp_v0_2)->unk_10 = temp_s5;
                temp_s0 = ((S_800D5294_3 *)temp_v0_2)->unk_08;
                temp_v0 = rand() & 0x3F;
                temp_v1 = temp_s0->unk_02;
                temp_v1 = temp_v1 - 0x1F;
                temp_s0->unk_02 = temp_v1 + temp_v0;
                temp_v0 = rand() & 0x3F;
                temp_v1 = temp_s0->unk_06;
                temp_v1 = temp_v1 - 0x1F;
                temp_s0->unk_06 = temp_v1 + temp_v0;
                temp_v0 = rand() & 0x1F;
                temp_s0->unk_0A = (s16) (temp_s0->unk_0A - temp_v0);
                temp_s0->unk_14 = (s32) ((0 - ((rand() & 0xFFFF) + 0x10000)) * 2);
            }
            var_s1 += 1;
        } while (var_s1 < 4);
    }
    temp_v0_4 = ((S_800D5294_0 *)arg0)->unk_1E - 1;
    ((S_800D5294_0 *)arg0)->unk_1E = temp_v0_4;
    if ((temp_v0_4 << 0x10) <= 0) {
        ((S_800D5294_0_pre *)arg0)[-1].unk_00 = (u16) (((S_800D5294_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        fixed = D_80083460;
        fixed[5] = fixed[5] - 1;
    }
}
