#include "common.h"
#include "m2c_compat.h"

typedef struct S_818C3898_0_pre {
    u16 unk_00;
} S_818C3898_0_pre;   /* the 0x2 bytes before arg0 in func_818C3898, addressed as arg0[-1] */

typedef struct S_818C3898_0 {
    void * unk_00;
    u8 pad_04[0xC];
    u16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
} S_818C3898_0;   /* arg0 in func_818C3898 */

typedef struct S_818C3898_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_818C3898_1;   /* temp_v1 in func_818C3898 */

typedef struct S_818C3898_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818C3898_2;   /* arg2 in func_818C3898 */

typedef struct S_818C3898_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818C3898_3;   /* temp_arg1 in func_818C3898 */

typedef struct S_818C3898_4 {
    s32 unk_00;
} S_818C3898_4;   /* temp_d in func_818C3898 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800814A0[3];
extern void func_800478B8(void *arg0);
void func_818C3898(void *arg0, void *arg1, S_818C3898_2 *arg2) {
    s16 temp_lo;
    s32 temp_s0;
    s32 var_v1;
    s32 var_v1_adj;
    s32 temp_a0;
    u16 temp_v0;
    S_818C3898_1 *temp_v1;
    S_818C3898_3 *temp_arg1;
    s32 *temp_d;

    temp_v1 = ((S_818C3898_0 *)arg0)->unk_00;
    temp_arg1 = arg1;
    temp_v1->unk_0C = (u16) (temp_v1->unk_0C + 1);
    temp_v0 = ((S_818C3898_0 *)arg0)->unk_10;
    temp_v0 = (u16) (temp_v0 + 1);
    temp_s0 = (s16) temp_v0;
    ((S_818C3898_0 *)arg0)->unk_10 = temp_v0;
    temp_s0 = temp_s0 % 7;
    temp_s0 += 1;
    func_800478B8(arg2);
    var_v1 = (s16) temp_s0;
    arg2->unk_1A = (u16) (arg2->unk_1A + 0x300);
    var_v1_adj = var_v1;
    if (var_v1 < 0) {
        var_v1_adj = var_v1 + 3;
    }
    temp_a0 = (s32) (var_v1 + ((u32) (temp_s0 << 0x10) >> 0x1F)) >> 1;
    arg2->unk_0C = (s8) ((var_v1_adj >> 2) << 7);
    arg2->unk_0D = (s8) ((s32) (((s16) temp_a0 - (((s32) ((s16) temp_a0 + ((u32) (temp_a0 << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9);
    arg2->unk_0E = (s8) ((s32) ((var_v1 - (temp_a0 * 2)) << 0x10) >> 9);
    temp_lo = (0x1400 / (s16) ((S_818C3898_0 *)arg0)->unk_14) * (s16) ((S_818C3898_0 *)arg0)->unk_10;
    arg2->unk_1E = temp_lo;
    arg2->unk_1C = temp_lo;
    temp_arg1->unk_00 = (s32) (temp_arg1->unk_00 + temp_arg1->unk_0C);
    temp_arg1->unk_04 = (s32) (temp_arg1->unk_04 + temp_arg1->unk_10);
    temp_arg1->unk_08 = (s32) (temp_arg1->unk_08 + temp_arg1->unk_14);
    if ((s16) ((S_818C3898_0 *)arg0)->unk_10 > ((S_818C3898_0 *)arg0)->unk_14) {
        ((S_818C3898_0_pre *)arg0)[-1].unk_00 = (u16) (((S_818C3898_0_pre *)arg0)[-1].unk_00 | 0x8000);
        temp_d = D_800814A0;
        ((S_818C3898_4 *)temp_d)->unk_00 = (s32) (((S_818C3898_4 *)temp_d)->unk_00 | 0x8000);
    }
}
