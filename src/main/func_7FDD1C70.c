/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80088BD0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    union { s16 s16; void * p32; } unk_20;   /* accessed as both */
    u8 pad_24[0xA];
    s16 unk_2E;
} S_80088BD0_0;   /* temp_v0 in func_80088BD0 */

typedef struct S_80088BD0_1 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x4];
    s16 unk_22;
} S_80088BD0_1;   /* var_fp in func_80088BD0 */

typedef struct S_80088BD0_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80088BD0_2;   /* var_s5 in func_80088BD0 */

typedef struct S_80088BD0_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_80088BD0_3;   /* temp_s1 in func_80088BD0 */

typedef struct S_80088BD0_4 {
    s32 unk_00;
} S_80088BD0_4;   /* (s8 *)stack_desc + (s32)var_s4 in func_80088BD0 */

typedef struct S_80088BD0_5 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80088BD0_5;   /* (s8 *)temp_s3 - 0x20 in func_80088BD0 */

typedef struct S_80088BD0_6 {
    void * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
    s16 unk_0C;
} S_80088BD0_6;   /* temp_s3 in func_80088BD0 */

typedef struct S_80088BD0_7 {
    u8 pad_00[0x4];
    void * unk_04;
    s32 unk_08;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
} S_80088BD0_7;   /* temp_v1 in func_80088BD0 */

typedef struct S_80088BD0_8 {
    u8 pad_00[0x10];
    void * unk_10;
} S_80088BD0_8;   /* (s8 *)var_fp + (var_s2 << 2) in func_80088BD0 */

typedef struct S_80088BD0_9 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_80088BD0_9;   /* ((S_80088BD0_0 *)temp_v0)->unk_08 in func_80088BD0 */


M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64(); /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80044BB0;
extern s32 D_80053A88;
extern s8 D_80080A84;
extern M2C_UNK D_80088760;
extern M2C_UNK D_8008896C;
void func_80088B48();  /* extern */
void func_80088EDC();  /* extern */
void func_800890EC();  /* extern */
void func_80089608();  /* extern */
void func_80089A38();  /* extern */
extern M2C_UNK D_8008B230;
extern M2C_UNK D_8008B270;

typedef struct { s32 a, b, c; } Desc3;

void func_80088BD0(void) {
    s32 stack_desc[3];
    s32 var_s2;
    s32 var_s6;
    s32 var_s7;
    s32 const_1000;
    s32 idxval;
    void *temp_s3;
    S_80088BD0_3 *temp_s1;
    void *temp_v0;
    S_80088BD0_7 *temp_v1;
    void *var_fp;
    void *var_s4;
    void *var_s5;

    var_fp = NULL;
    *(Desc3 *)stack_desc = *(Desc3 *)&D_80088760;
    D_80080A84 = 1;
    temp_v0 = func_8003FC64(0x11);
    if (temp_v0 != NULL) {
        var_fp = temp_v0 + 0x20;
        ((S_80088BD0_0 *)temp_v0)->unk_10 = (void *)func_800890EC;
        func_8004491C(temp_v0, &D_8008896C);
        ((S_80088BD0_1 *)var_fp)->unk_22 = 0x708;
        ((S_80088BD0_9 *)(((S_80088BD0_0 *)temp_v0)->unk_08))->unk_06 = 0xF0;
        ((S_80088BD0_1 *)var_fp)->unk_1A = 0;
        ((S_80088BD0_1 *)var_fp)->unk_1C = 0x40;
    }
    var_s2 = 2;
    var_s7 = 0x3C;
    var_s6 = 0xC8;
    const_1000 = 0x1000;
    var_s5 = var_fp + 8;
    do {
        temp_v0 = func_8003FC64(0x111);
        ((S_80088BD0_2 *)var_s5)->unk_04 = temp_v0;
        var_s4 = (void *)(var_s2 << 2);
        if (temp_v0 != NULL) {
            temp_s3 = temp_v0 + 0x20;
            temp_s1 = ((S_80088BD0_0 *)temp_v0)->unk_0C;
            ((S_80088BD0_0 *)temp_v0)->unk_10 = (void *)func_80088EDC;
            func_8004491C(temp_v0, &D_80044BB0);
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)temp_v0)->unk_08))->unk_02 = -0x40;
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)temp_v0)->unk_08))->unk_06 = var_s6;
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)temp_v0)->unk_08))->unk_0C = 0x150000;
            temp_s1->unk_1E = const_1000;
            temp_s1->unk_1C = const_1000;
            idxval = ((S_80088BD0_4 *)((s8 *)stack_desc + (s32)var_s4))->unk_00;
            temp_s1->unk_04 = 0;
            temp_s1->unk_05 = 0;
            temp_s1->unk_0C = 0x808080;
            temp_s1->unk_08 = idxval;
            ((S_80088BD0_5 *)((s8 *)temp_s3 - 0x20))->unk_20 = var_fp;
            ((S_80088BD0_6 *)temp_s3)->unk_0C = var_s2;
            ((S_80088BD0_6 *)temp_s3)->unk_0A = var_s7;
        }
        var_s7 -= 0x1E;
        var_s6 -= 0x10;
        var_s2 -= 1;
        var_s5 -= 4;
    } while (var_s2 >= 0);
    temp_v0 = func_8003FC64(1);
    if (temp_v0 != NULL) {
        ((S_80088BD0_0 *)temp_v0)->unk_10 = (void *)func_80088B48;
        func_8004491C(temp_v0, &D_80053A88);
        temp_v1 = temp_v0 + 0x20;
        temp_v1->unk_0C = 0x60;
        temp_v1->unk_0E = -0x100;
        temp_v1->unk_10 = 0x80;
        temp_v1->unk_12 = 0x10;
        temp_v1->unk_14 = 0;
        temp_v1->unk_16 = 3;
        temp_v1->unk_08 = 0x606060;
        ((S_80088BD0_0 *)temp_v0)->unk_20.s16 = 0;
        temp_v1->unk_04 = var_fp;
    }
    var_s2 = 1;
    do {
        temp_v0 = func_8003FC64(0x111);
        ((S_80088BD0_8 *)((s8 *)var_fp + (var_s2 << 2)))->unk_10 = temp_v0;
        if (temp_v0 != NULL) {
            temp_s3 = temp_v0 + 0x20;
            temp_s1 = ((S_80088BD0_0 *)temp_v0)->unk_0C;
            ((S_80088BD0_0 *)temp_v0)->unk_10 = (void *)func_80089A38;
            func_8004491C(temp_v0, &D_80044BB0);
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)temp_v0)->unk_08))->unk_06 = 0xE9;
            if (var_s2 != 0) {
                ((S_80088BD0_9 *)(((S_80088BD0_0 *)temp_v0)->unk_08))->unk_02 = -0x15;
                ((S_80088BD0_9 *)(((S_80088BD0_0 *)temp_v0)->unk_08))->unk_0C = 0x160000;
                func_8003DB94(temp_s1, &D_8008B270, 0);
                goto common_tail;
            }
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)temp_v0)->unk_08))->unk_02 = 0x155;
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)temp_v0)->unk_08))->unk_0C = 0xFFEA0000;
            func_8003DB94(temp_s1, &D_8008B230, 0);
common_tail:
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)temp_v0)->unk_08))->unk_10 = 0xFFF80000;
            temp_s1->unk_1E = 0x1000;
            temp_s1->unk_1C = 0x1000;
            temp_s1->unk_0C = 0x808080;
            ((S_80088BD0_6 *)temp_s3)->unk_00 = var_fp;
            ((S_80088BD0_6 *)temp_s3)->unk_0C = var_s2;
        }
        var_s2 -= 1;
    } while (var_s2 >= 0);
    temp_v0 = func_8003FC64(1);
    if (temp_v0 != NULL) {
        ((S_80088BD0_0 *)temp_v0)->unk_10 = (void *)func_80089608;
        ((S_80088BD0_0 *)temp_v0)->unk_20.p32 = var_fp;
        ((S_80088BD0_0 *)temp_v0)->unk_2E = 0xE00;
    }
}
