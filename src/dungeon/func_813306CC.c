#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80167540[3];
extern u8 D_80045340[];
extern u8 D_800DEAE0[];
extern void *func_8003FC64(s32);
extern M2C_UNK func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s32);

typedef struct S_801676CC_0 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
} S_801676CC_0;   /* temp_v0_2 in func_801676CC */

typedef struct S_801676CC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_801676CC_1;   /* temp_v0 in func_801676CC */

typedef struct S_801676CC_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_801676CC_2;   /* temp_a0 in func_801676CC */

typedef struct S_801676CC_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801676CC_3;   /* temp_a0_2 in func_801676CC */

typedef struct S_801676CC_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801676CC_4;   /* arg0 in func_801676CC */

typedef struct S_801676CC_5 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_801676CC_5;   /* temp_a0_3 in func_801676CC */

void func_801676CC(S_801676CC_4 *arg0) {
    s16 var_s1;
    s16 var_s2;
    s32 var_s3;
    s16 var_s5;
    void *var_s6;
    S_801676CC_2 *temp_a0;
    S_801676CC_3 *temp_a0_2;
    S_801676CC_5 *temp_a0_3;
    void *temp_v0;
    S_801676CC_0 *temp_v0_2;

    var_s3 = 0;
    var_s5 = 0xE;
    var_s6 = &D_80167540;
    var_s2 = 0x1000;
    var_s1 = 0x1400;
    do {
        temp_v0 = func_8003FC64(0x212);
        if (temp_v0 != NULL) {
            temp_v0_2 = temp_v0 + 0x20;
            temp_v0_2->unk_18 = var_s5;
            temp_v0_2->unk_1A = var_s5;
            ((S_801676CC_1 *)temp_v0)->unk_10 = var_s6;
            func_8004491C(temp_v0, D_80045340);
            temp_a0 = ((S_801676CC_1 *)temp_v0)->unk_0C;
            temp_a0->unk_10 = 0x60;
            temp_a0->unk_14 = (u16) (temp_a0->unk_14 | 0xC);
            temp_a0_2 = ((S_801676CC_1 *)temp_v0)->unk_08;
            temp_a0_2->unk_00 = (s32) arg0->unk_00;
            temp_a0_2->unk_04 = (s32) arg0->unk_04;
            temp_a0_2->unk_08 = (s32) (arg0->unk_08 + 0xFFC00000);
            temp_a0_3 = ((S_801676CC_1 *)temp_v0)->unk_0C;
            temp_a0_3->unk_1C = var_s1;
            temp_a0_3->unk_1E = var_s2;
            temp_a0_3->unk_0E = 0;
            temp_a0_3->unk_0D = 0;
            temp_a0_3->unk_0C = 0;
            temp_a0_3->unk_06 = 0;
            temp_a0_3->unk_12 = 0x7DCF;
            temp_a0_3->unk_14 = (u16) (temp_a0_3->unk_14 | 0x100);
            func_8003DB94(temp_a0_3, D_800DEAE0, 0);
        }
        var_s2 += 0x200;
        var_s3 += 1;
        var_s1 += 0x200;
    } while (var_s3 < 0x10);
}
