/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AECA4_2 {
    u8 pad_00[0xD8];
    void * unk_D8;
} S_800AECA4_2;   /* arg0 in func_800AECA4 */

typedef struct S_800AECA4_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x14];
    void * unk_20;
    u8 pad_24[0x14];
    void * unk_38;
} S_800AECA4_3;   /* base in func_800AECA4 */

typedef struct S_800AECA4_4 {
    u8 pad_00[0x50];
    void * unk_50;
} S_800AECA4_4;   /* temp_s0 in func_800AECA4 */

typedef struct S_800AECA4_5 {
    s32 * unk_00;
    M2C_UNK ** unk_04;
} S_800AECA4_5;   /* ((S_800AECA4_2 *)arg0)->unk_D8 in func_800AECA4 */

typedef struct S_800AECA4_6 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AECA4_6;   /* ((S_800AECA4_3 *)base)->unk_38 in func_800AECA4 */

typedef struct S_800AECA4_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AECA4_7;   /* ((S_800AECA4_3 *)base)->unk_08 in func_800AECA4 */

typedef struct S_800AECA4_8 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AECA4_8;   /* ((S_800AECA4_3 *)base)->unk_20 in func_800AECA4 */

typedef struct S_800AECA4_9 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AECA4_9;   /* ((S_800AECA4_4 *)temp_s0)->unk_50 in func_800AECA4 */

typedef struct S_800AECA4_10 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AECA4_10;   /* ((S_800AECA4_5 *)(((S_800AECA4_2 *)arg0)->unk_D8))->unk_00 in func_800AECA4 */

typedef struct S_800AECA4_11 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800AECA4_11;   /* ((S_800AECA4_6 *)(((S_800AECA4_3 *)base)->unk_38))->unk_04 in func_800AECA4 */

typedef struct S_800AECA4_12 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800AECA4_12;   /* ((S_800AECA4_7 *)(((S_800AECA4_3 *)base)->unk_08))->unk_04 in func_800AECA4 */

typedef struct S_800AECA4_13 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800AECA4_13;   /* ((S_800AECA4_8 *)(((S_800AECA4_3 *)base)->unk_20))->unk_04 in func_800AECA4 */

typedef struct S_800AECA4_14 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800AECA4_14;   /* ((S_800AECA4_9 *)(((S_800AECA4_4 *)temp_s0)->unk_50))->unk_04 in func_800AECA4 */

typedef struct S_800AECA4_15 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800AECA4_15;   /* ((S_800AECA4_10 *)(((S_800AECA4_5 *)(((S_800AECA4_2 *)arg0)->unk_D8))->unk_00))->unk_04 in func_800AECA4 */




int func_80049E6C();
s32 func_8004DC14();
s32 func_800AE4E4();
M2C_UNK func_800AE854();
extern u8 D_80077E84[12];
extern u8 D_80077EF0[12];
extern u8 D_80077EFC[12];

typedef struct S_800AECA4_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x1C];
    s32 unk_28;
    u8 pad_2C[0xC];
    u8 * unk_38;
    u8 pad_3C[0x9C];
    void * unk_D8;
} S_800AECA4_0;   /* arg0 in func_800AECA4 */

typedef struct S_800AECA4_1 {
    u8 pad_00[0x8];
    M2C_UNK ** unk_08;
    u8 pad_0C[0x14];
    M2C_UNK ** unk_20;
    u8 pad_24[0x14];
    void ** unk_38;
    u8 pad_3C[0x14];
    s32 * unk_50;
} S_800AECA4_1;   /* base in func_800AECA4 */

void func_800AECA4(void *arg0) {
    s16 var_s2;
    s16 var_s4;
    s32 temp_s0;
    s32 var_s3;

    *((S_800AECA4_5 *)(((S_800AECA4_2 *)arg0)->unk_D8))->unk_04 = &D_80077E84;
    var_s3 = 0;
    *((S_800AECA4_5 *)(((S_800AECA4_2 *)arg0)->unk_D8))->unk_00 = func_80049E6C(((S_800AECA4_0 *)arg0)->unk_28);
    ((S_800AECA4_15 *)(((S_800AECA4_10 *)(((S_800AECA4_5 *)(((S_800AECA4_2 *)arg0)->unk_D8))->unk_00))->unk_04))->unk_0A = (s16) ((((S_800AECA4_0 *)arg0)->unk_28 * 8) + 2);
    if (((S_800AECA4_0 *)arg0)->unk_28 > 0) {
        u8 *var_s6 = D_80077EF0;
        u8 *var_s5 = D_80077EFC;
        var_s4 = 0x82;
        var_s2 = 0xA;
        do {
            temp_s0 = var_s3 * 4;
            {
                register u8 *base ASM_REG("$2") = ((S_800AECA4_0 *)arg0)->unk_D8;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                base = (u8 *)(temp_s0 + (s32)base);
                ((S_800AECA4_11 *)(((S_800AECA4_6 *)(((S_800AECA4_3 *)base)->unk_38))->unk_04))->unk_0A = var_s2;
            }
            {
                register u8 *base ASM_REG("$2") = ((S_800AECA4_0 *)arg0)->unk_D8;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                base = (u8 *)(temp_s0 + (s32)base);
                *((S_800AECA4_1 *)base)->unk_38 = arg0 + 0x40;
            }
            {
                register u8 *base ASM_REG("$2") = ((S_800AECA4_0 *)arg0)->unk_D8;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                base = (u8 *)(temp_s0 + (s32)base);
                ((S_800AECA4_12 *)(((S_800AECA4_7 *)(((S_800AECA4_3 *)base)->unk_08))->unk_04))->unk_0A = var_s2;
            }
            {
                register u8 *base ASM_REG("$2") = ((S_800AECA4_0 *)arg0)->unk_D8;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                base = (u8 *)(temp_s0 + (s32)base);
                *((S_800AECA4_1 *)base)->unk_08 = var_s6;
            }
            {
                register u8 *base ASM_REG("$2") = ((S_800AECA4_0 *)arg0)->unk_D8;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                base = (u8 *)(temp_s0 + (s32)base);
                ((S_800AECA4_13 *)(((S_800AECA4_8 *)(((S_800AECA4_3 *)base)->unk_20))->unk_04))->unk_0A = var_s2;
            }
            {
                register u8 *base ASM_REG("$2") = ((S_800AECA4_0 *)arg0)->unk_D8;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                base = (u8 *)(temp_s0 + (s32)base);
                *((S_800AECA4_1 *)base)->unk_20 = var_s5;
            }
            var_s2 += 0x10;
            {
                s32 result = func_8004DC14(func_800AE4E4(*(((S_800AECA4_0 *)arg0)->unk_38 + var_s3)), 1);
                register u8 *base ASM_REG("$3") = ((S_800AECA4_0 *)arg0)->unk_D8;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                base = (u8 *)(temp_s0 + (s32)base);
                *((S_800AECA4_1 *)base)->unk_50 = result;
            }
            var_s3 += 1;
            temp_s0 = temp_s0 + ((S_800AECA4_0 *)arg0)->unk_D8;
            ((S_800AECA4_14 *)(((S_800AECA4_9 *)(((S_800AECA4_4 *)temp_s0)->unk_50))->unk_04))->unk_0A = var_s4;
            var_s4 += 0x10;
        } while (var_s3 < ((S_800AECA4_0 *)arg0)->unk_28);
    }
    ((S_800AECA4_0 *)arg0)->unk_04 = 1;
    ((S_800AECA4_0 *)arg0)->unk_08 = 1;
    func_800AE854(arg0);
}
