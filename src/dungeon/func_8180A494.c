#include "common.h"
#include "m2c_compat.h"

typedef struct S_80025C94_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x2C];
    void * unk_58;
    M2C_UNK (*unk_5C)(void *, void *, void *, void *);
    u8 pad_60[0xA];
    s16 unk_6A;
    u8 pad_6C[0x6];
    union { s8 s; u8 u; } unk_72;   /* accessed as both */
    union { s8 s; u8 u; } unk_73;   /* accessed as both */
    u8 pad_74[0x14];
    s16 unk_88;
} S_80025C94_0;   /* temp_s0 in func_80025C94 */

typedef struct S_80025C94_1 {
    u8 pad_00[0x92];
    s16 unk_92;
    u8 pad_94[0x2];
    s16 unk_96;
    u8 pad_98[0x5];
    s8 unk_9D;
} S_80025C94_1;   /* temp_a3 in func_80025C94 */

typedef struct S_80025C94_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_80025C94_2;   /* temp_s1 in func_80025C94 */

typedef struct S_80025C94_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_80025C94_3;   /* temp_s2 in func_80025C94 */

typedef struct S_80025C94_4 {
    u8 pad_00[0xC8];
    u16 unk_C8;
} S_80025C94_4;   /* temp_s5 in func_80025C94 */

typedef struct S_80025C94_5 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
} S_80025C94_5;   /* temp_s3 in func_80025C94 */

typedef struct S_80025C94_6 {
    u8 pad_00[0x2094];
    u16 unk_2094;
} S_80025C94_6;   /* (s8 *)temp_table + (((S_80025C94_0 *)temp_s0)->unk_6A * 2) in func_80025C94 */

typedef struct S_80025C94_7_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80025C94_7_pre;   /* the 0x14 bytes before ((S_80025C94_0 *)temp_s0)->unk_58 in func_80025C94, addressed as ((S_80025C94_0 *)temp_s0)->unk_58[-1] */

typedef struct S_80025C94_7 {
    u8 pad_00[0x26];
    s16 unk_26;
} S_80025C94_7;   /* ((S_80025C94_0 *)temp_s0)->unk_58 in func_80025C94 */


extern s16 D_80027156;
extern s16 D_80027158;
extern s16 D_8002715A;
extern u16 D_8002715C;
extern s8 D_8006CCD8[];
extern s8 D_8006CCE8[];
extern s8 D_80083160[];
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];

void func_80025C94(void *arg0, void *arg1, void *arg2) {
    s16 temp_a0_2;
    s32 temp_v0_3;
    s32 temp_v1_2;
    s8 temp_a0;
    s8 temp_v0;
    s8 temp_v1;
    u16 temp_s4;
    u16 temp_counter;
    u8 temp_v0_2;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 temp_v1_5;
    u8 temp_v1_6;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    u16 *temp_table;
    register S_80025C94_1 *temp_a3 ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
    S_80025C94_0 *temp_s0;
    S_80025C94_2 *temp_s1;
    S_80025C94_3 *temp_s2;
    S_80025C94_5 *temp_s3;
    S_80025C94_4 *temp_s5;
    void *var_a0;

    temp_counter = D_8002715C;
    var_a0 = arg0;
    temp_a3 = var_a0;
    temp_s2 = arg1;
    temp_s1 = arg2;
    temp_s0 = temp_a3;
    D_8002715C = temp_counter + 1;
    temp_s5 = D_80083160;
    temp_v1 = temp_s0->unk_72.s;
    if (temp_v1 == 1) {
        goto block_10;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto block_state0;
        }
        temp_a3->unk_96 = 0;
        goto block_epilogue;
    }
    if (temp_v1 == 2) {
        goto block_14;
    }
    if (temp_v1 == 3) {
        goto block_state3;
    }
    temp_a3->unk_96 = 0;
    goto block_epilogue;
block_state0:
    temp_s1->unk_1E = 0x1000;
    temp_s1->unk_1C = 0x1000;
    temp_s1->unk_0E = 0U;
    temp_s1->unk_0D = 0U;
    temp_s1->unk_0C = 0U;
    temp_s0->unk_73.s = 8;
    temp_s0->unk_2A = 0x400;
    temp_table = (u16 *)0x80010000;
    temp_v1_2 = (((S_80025C94_6 *)((s8 *)temp_table + (temp_s0->unk_6A * 2)))->unk_2094 + 2) & 7;
    temp_s2->unk_00.at02.v = D_800DCEAC[temp_v1_2];
    temp_v0_3 = D_800DCEBC[temp_v1_2];
    temp_s2->unk_0A = 0;
    temp_s2->unk_04.at02.v = temp_v0_3;
    temp_s1->unk_24 = (u8) (D_8006CCD8[temp_v1_2 * 2] + 1);
    temp_s1->unk_25 = (u8) (D_8006CCE8[temp_v1_2 * 2] + 1);
    temp_s0->unk_72.s = (s8) ((u8) temp_s0->unk_72.s + 1);
block_10:
    var_a0 = (void *) temp_s0->unk_73.s;
    if (var_a0 != NULL) {
        temp_v1_5 = temp_s1->unk_0E;
        temp_v1_6 = temp_v1_5 + ((s32) (0x80 - temp_v1_5) / (s32) var_a0);
        temp_s1->unk_0E = temp_v1_6;
        temp_s1->unk_0D = temp_v1_6;
        temp_s1->unk_0C = temp_v1_6;
    }
    temp_v0_2 = temp_s0->unk_73.u - 1;
    temp_s0->unk_73.u = temp_v0_2;
    if ((temp_v0_2 << 0x18) > 0) {
        goto block_14;
    }
    temp_s1->unk_0E = 0x80U;
    temp_s1->unk_0D = 0x80U;
    temp_s1->unk_0C = 0x80U;
    temp_s0->unk_73.u = 0U;
    temp_s0->unk_72.u = (u8) (temp_s0->unk_72.u + 1);
block_14:
    if (D_8002715A == 0) {
        goto block_22;
    }
    temp_s0->unk_73.u = 8U;
    temp_s2->unk_16 = 8;
    goto block_advance_state;
block_state3:
    temp_a0 = temp_s0->unk_73.s;
    if (temp_a0 != 0) {
        temp_v1_3 = temp_s1->unk_0E;
        temp_v1_4 = temp_v1_3 + ((s32) (0 - temp_v1_3) / temp_a0);
        temp_s1->unk_0E = temp_v1_4;
        temp_s1->unk_0D = temp_v1_4;
        temp_s1->unk_0C = temp_v1_4;
    }
    temp_v0 = (u8) temp_s0->unk_73.s - 1;
    temp_s0->unk_73.s = temp_v0;
    if ((temp_v0 << 0x18) > 0) {
        goto block_22;
    }
block_advance_state:
    temp_s0->unk_72.u = (u8) (temp_s0->unk_72.u + 1);
block_22:
    temp_a0_2 = temp_a3->unk_96;
    if (temp_a0_2 != 0) {
        temp_s2->unk_00.at00.v = (s32) (temp_s2->unk_00.at00.v + ((s32) ((((temp_s1->unk_24 - 1) << 6) - (s16) temp_s2->unk_00.at02.v) << 0x10) / temp_a0_2));
        temp_s2->unk_04.at00.v = (s32) (temp_s2->unk_04.at00.v + ((s32) ((((temp_s1->unk_25 - 1) << 6) - (s16) temp_s2->unk_04.at02.v) << 0x10) / (s16) temp_a3->unk_96));
        temp_v0_3 = (u16) temp_a3->unk_96 - 1;
        temp_a3->unk_96 = temp_v0_3;
        if ((temp_v0_3 << 0x10) <= 0) {
            temp_a3->unk_96 = 0;
        }
    }
    if (temp_s0->unk_14 & 0x40000) {
        temp_a3->unk_92 = -0x20;
        goto block_after_92;
    }
    temp_a3->unk_92 = 0;
block_after_92:
    temp_a3->unk_9D = 0;
    temp_s3 = ((S_80025C94_7_pre *)(temp_s0->unk_58))[-1].unk_00;
    temp_s4 = temp_s5->unk_C8;
    temp_s5->unk_C8 = (u16) temp_s3->unk_1A;
    temp_s1->unk_14 = (u16) (temp_s1->unk_14 & 0xFFBF);
    temp_s2->unk_00.at02.v = (u16) (temp_s2->unk_00.at02.v + 0x100);
    temp_s2->unk_04.at02.v = (u16) (temp_s2->unk_04.at02.v + 0x100);
    if (D_80027158 == temp_s0->unk_6A) {
        temp_v0_3 = (D_80027156 << 9) + 0x400;
        goto block_store_2a;
    }
    temp_v0_3 = 0x400;
block_store_2a:
    temp_s0->unk_2A = temp_v0_3;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_s0->unk_5C(temp_a3, temp_s2, temp_s1, temp_a3);
    temp_s2->unk_00.at02.v = (u16) (temp_s2->unk_00.at02.v - 0x100);
    temp_s2->unk_04.at02.v = (u16) (temp_s2->unk_04.at02.v - 0x100);
    temp_s5->unk_C8 = temp_s4;
    temp_s0->unk_88 = 0;
    var_a0_2 = temp_s3->unk_0C;
    if (temp_s0->unk_6A != ((S_80025C94_7 *)(temp_s0->unk_58))->unk_26) {
        var_a0_2 = var_a0_2 >> 1;
    }
    temp_s1->unk_0C = var_a0_2;
    var_a0_3 = temp_s3->unk_0D;
    if (temp_s0->unk_6A != ((S_80025C94_7 *)(temp_s0->unk_58))->unk_26) {
        var_a0_3 = var_a0_3 >> 1;
    }
    temp_s1->unk_0D = var_a0_3;
    var_a0_4 = temp_s3->unk_0E;
    if (temp_s0->unk_6A != ((S_80025C94_7 *)(temp_s0->unk_58))->unk_26) {
        var_a0_4 = var_a0_4 >> 1;
    }
    temp_s1->unk_0E = var_a0_4;
    goto block_epilogue;
block_epilogue:
    return;
}
