/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
void func_8004491C(void *, void *); /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern u8 D_800250B4[];
extern u8 D_80028220[];
extern u8 D_80045C34[];

typedef struct S_81959B44_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_81959B44_0;   /* temp_v0 in func_81959B44 */

typedef struct S_81959B44_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_81959B44_1;   /* temp_s2 in func_81959B44 */

typedef struct S_81959B44_2 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    u8 pad_22[0xE];
    s16 unk_30;
    u8 pad_32[0x6];
    s16 unk_38;
    u8 pad_3A[0x2];
    u16 unk_3C;
} S_81959B44_2;   /* temp_s0 in func_81959B44 */

typedef struct S_81959B44_3 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 pad_0C[0xA];
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
} S_81959B44_3;   /* temp_s2_2 in func_81959B44 */

void *func_81959B44(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 subroutine_arg4;
    s32 subroutine_arg6;
    s32 subroutine_arg8;
    s32 sp28;
    M2C_UNK var_a0;
    s16 temp_s1_2;
    s16 temp_s3_3;
    s32 var_s6;
    s32 temp_lo;
    s32 temp_s1;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_s4;
    s32 temp_v0_2;
    s32 temp_v0_3;
    S_81959B44_2 *temp_s0;
    S_81959B44_1 *temp_s2;
    S_81959B44_3 *temp_s2_2;
    void *temp_v0;

    var_s6 = 0;
    sp28 = 0x2AAAAAAB;
    do {
        var_a0 = 0x12;
        if (arg3 != 0) {
            var_a0 = 0x212;
        }
        temp_v0 = func_8003FC64(var_a0);
        if (temp_v0 != NULL) {
            ((S_81959B44_0 *)temp_v0)->unk_10 = &D_800250B4;
            func_8004491C(temp_v0, &D_80045C34);
            temp_s4 = var_s6 << 8;
            temp_s2 = ((S_81959B44_0 *)temp_v0)->unk_08;
            temp_s3 = func_80064584(temp_s4) >> 7;
            temp_s3_2 = temp_s3 + ((s32) ((s16) temp_s3 * arg3) >> 2);
            temp_s1 = func_800644B8(temp_s4) >> 7;
            temp_lo = (s16) temp_s1 * arg3;
            temp_s0 = temp_v0 + 0x20;
            temp_s3_3 = arg0 + temp_s3_2;
            temp_s2->unk_02 = temp_s3_3;
            temp_s0->unk_1C = temp_s3_3;
            temp_s1_2 = arg1 + (temp_s1 + (temp_lo >> 2));
            temp_s2->unk_06 = temp_s1_2;
            temp_s0->unk_1E = temp_s1_2;
            temp_s2->unk_0A = arg2;
            temp_s0->unk_20 = arg2;
            temp_s2_2 = ((S_81959B44_0 *)temp_v0)->unk_0C;
            temp_s2_2->unk_08 = &D_80028220;
            temp_s2_2->unk_1C = 0x1000;
            temp_s2_2->unk_1A = (u16) (temp_s4 + 0x400);
            temp_v0_2 = 0 - (func_800644B8(temp_s4) << 0xC);
            temp_s2_2->unk_16 = (s16) ((temp_v0_2 / 6) >> 0xC);
            temp_v0_3 = func_80064584(temp_s4) << 0xC;
            temp_s2_2->unk_18 = (s16) ((temp_v0_3 / 6) >> 0xC);
            temp_s0->unk_14 = temp_s3_3;
            temp_s0->unk_16 = temp_s1_2;
            temp_s0->unk_18 = arg2;
            temp_s0->unk_38 = var_s6;
            temp_s0->unk_30 = (s16) (arg3 + 4);
            temp_s0->unk_3C = (u16) arg3;
        }
        var_s6 += 1;
    } while (var_s6 < 0x10);
    return temp_v0;
}
