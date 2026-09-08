#include "common.h"
#include "m2c_compat.h"

/* first_pass warm draft: compiles, best score 106 @ 2.7.2 */
#include "common.h"

typedef struct S_800500B4_4 {
    u8 pad_00[0x20];
    void * unk_20;
    void * unk_24;
} S_800500B4_4;   /* arg0 in func_800500B4 */

typedef struct S_800500B4_5 {
    u8 pad_00[0x4];
    void * unk_04;
    void * unk_08;
} S_800500B4_5;   /* temp_v1 in func_800500B4 */

typedef struct S_800500B4_6 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x18];
    void * unk_20;
    u8 pad_24[0x4];
    void * unk_28;
} S_800500B4_6;   /* var_a3 in func_800500B4 */

typedef struct S_800500B4_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800500B4_7;   /* temp_a0 in func_800500B4 */

typedef struct S_800500B4_8 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800500B4_8;   /* ((S_800500B4_4 *)arg0)->unk_20 in func_800500B4 */

typedef struct S_800500B4_9 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800500B4_9;   /* ((S_800500B4_4 *)arg0)->unk_24 in func_800500B4 */

typedef struct S_800500B4_10 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800500B4_10;   /* ((S_800500B4_5 *)temp_v1)->unk_08 in func_800500B4 */

typedef struct S_800500B4_11 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800500B4_11;   /* ((S_800500B4_5 *)temp_v1)->unk_04 in func_800500B4 */

typedef struct S_800500B4_12 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800500B4_12;   /* ((S_800500B4_6 *)var_a3)->unk_20 in func_800500B4 */

typedef struct S_800500B4_13 {
    u8 pad_00[0x4];
    s8 * unk_04;
} S_800500B4_13;   /* ((S_800500B4_6 *)var_a3)->unk_04 in func_800500B4 */

typedef struct S_800500B4_14 {
    u8 pad_00[0x4];
    s8 * unk_04;
} S_800500B4_14;   /* ((S_800500B4_6 *)var_a3)->unk_28 in func_800500B4 */

typedef struct S_800500B4_15 {
    u8 pad_00[0x2];
    s8 unk_02;
} S_800500B4_15;   /* ((S_800500B4_7 *)temp_a0)->unk_04 in func_800500B4 */

typedef struct S_800500B4_16 {
    u8 pad_00[0xA];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
} S_800500B4_16;   /* ((S_800500B4_8 *)(((S_800500B4_4 *)arg0)->unk_20))->unk_04 in func_800500B4 */

typedef struct S_800500B4_17 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800500B4_17;   /* ((S_800500B4_9 *)(((S_800500B4_4 *)arg0)->unk_24))->unk_04 in func_800500B4 */

typedef struct S_800500B4_18 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_800500B4_18;   /* ((S_800500B4_12 *)(((S_800500B4_6 *)var_a3)->unk_20))->unk_08 in func_800500B4 */

typedef struct S_800500B4_19 {
    u8 pad_00[0x1];
    s8 unk_01;
    u8 pad_02[0x6];
    s16 unk_08;
} S_800500B4_19;   /* ((S_800500B4_13 *)(((S_800500B4_6 *)var_a3)->unk_04))->unk_04 in func_800500B4 */

typedef struct S_800500B4_20 {
    u8 pad_00[0x1];
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x5];
    s16 unk_08;
} S_800500B4_20;   /* ((S_800500B4_14 *)(((S_800500B4_6 *)var_a3)->unk_28))->unk_04 in func_800500B4 */


typedef struct S_800500B4_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
} S_800500B4_0;   /* pArg1 in func_800500B4 */

typedef struct S_800500B4_1 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800500B4_1;   /* arg0 in func_800500B4 */

typedef struct S_800500B4_2 {
    u8 pad_00[0xA4];
    u8 unk_A4;
} S_800500B4_2;   /* var_a2 in func_800500B4 */

typedef struct S_800500B4_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800500B4_3;   /* var_a3 in func_800500B4 */


void func_800500B4(S_800500B4_1 *arg0, void *arg1) {
    S_800500B4_0 *pArg1;
    register s32 var_t1 ASM_REG("$9");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    register u8 *var_addr_a4 ASM_REG("$8");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_v1_3;
    u8 temp_a1_3;
    u8 temp_v1_2;
    u8 var_v0;
    S_800500B4_7 *temp_a0;
    S_800500B4_5 *temp_v1;
    void *var_a2;
    void *var_a3;
    s32 var_divres;

    pArg1 = arg1;
    temp_a1 = pArg1->unk_18;
    var_divres = (s32) ((pArg1->unk_1C - temp_a1) * (pArg1->unk_14 << 4)) / (s32) pArg1->unk_10;
    var_divres = var_divres - 0x28;
    ((S_800500B4_16 *)(((S_800500B4_8 *)(((S_800500B4_4 *)arg0)->unk_20))->unk_04))->unk_0A.s = (s16) ((temp_a1 << 4) + var_divres);
    ((S_800500B4_17 *)(((S_800500B4_9 *)(((S_800500B4_4 *)arg0)->unk_24))->unk_04))->unk_0A = (u16) ((S_800500B4_16 *)(((S_800500B4_8 *)(((S_800500B4_4 *)arg0)->unk_20))->unk_04))->unk_0A.u;
    temp_v1 = arg0->unk_20;
    ((S_800500B4_10 *)(temp_v1->unk_08))->unk_08 = (s16) (((S_800500B4_11 *)(temp_v1->unk_04))->unk_0A - 2);
    temp_a1_2 = pArg1->unk_1C;
    var_t1 = 0;
    var_a3 = arg0;
    var_a2 = pArg1;
    ((S_800500B4_18 *)(((S_800500B4_12 *)(((S_800500B4_6 *)var_a3)->unk_20))->unk_08))->unk_04 = (s16) (-(temp_a1_2 << 9) - ((s32) ((temp_a1_2 - pArg1->unk_18) * -(pArg1->unk_14 << 9)) / (s32) pArg1->unk_10));
    do {
        var_addr_a4 = (u8 *) ((s8 *) var_a2 + 0xA4);
        temp_a1_3 = *var_addr_a4;
        if (var_t1 == pArg1->unk_1C) {
            var_v0 = temp_a1_3 + ((s32) (8 - temp_a1_3) / (s32) ((pArg1->unk_10 - pArg1->unk_14) + 1));
        } else {
            var_v0 = temp_a1_3;
            if (var_v0 != 0) {
                var_v0 -= 1;
            }
        }
        *var_addr_a4 = var_v0;
        temp_v1_2 = ((S_800500B4_2 *)var_a2)->unk_A4;
        ((S_800500B4_19 *)(((S_800500B4_13 *)(((S_800500B4_6 *)var_a3)->unk_04))->unk_04))->unk_08 = (s16) temp_v1_2;
        var_t1 += 1;
        ((S_800500B4_20 *)(((S_800500B4_14 *)(((S_800500B4_6 *)var_a3)->unk_28))->unk_04))->unk_08 = (s16) (temp_v1_2 + 0x1E);
        *((S_800500B4_14 *)(((S_800500B4_6 *)var_a3)->unk_28))->unk_04 = (((S_800500B4_2 *)var_a2)->unk_A4 * 5) + 0x58;
        ((S_800500B4_20 *)(((S_800500B4_14 *)(((S_800500B4_6 *)var_a3)->unk_28))->unk_04))->unk_01 = (s8) ((((S_800500B4_2 *)var_a2)->unk_A4 * 5) + 0x58);
        ((S_800500B4_20 *)(((S_800500B4_14 *)(((S_800500B4_6 *)var_a3)->unk_28))->unk_04))->unk_02 = (s8) ((((S_800500B4_2 *)var_a2)->unk_A4 * 5) + 0x58);
        *((S_800500B4_13 *)(((S_800500B4_6 *)var_a3)->unk_04))->unk_04 = (((S_800500B4_2 *)var_a2)->unk_A4 * 5) + 0x58;
        ((S_800500B4_19 *)(((S_800500B4_13 *)(((S_800500B4_6 *)var_a3)->unk_04))->unk_04))->unk_01 = (s8) ((((S_800500B4_2 *)var_a2)->unk_A4 * 5) + 0x58);
        temp_a0 = ((S_800500B4_3 *)var_a3)->unk_04;
        var_a3 += 4;
        ((S_800500B4_15 *)(temp_a0->unk_04))->unk_02 = (s8) ((((S_800500B4_2 *)var_a2)->unk_A4 * 5) + 0x58);
        var_a2 += 1;
    } while (var_t1 < 6);
    temp_v1_3 = pArg1->unk_14;
    if (temp_v1_3 < pArg1->unk_10) {
        pArg1->unk_14 = (s32) (temp_v1_3 + 1);
    }
}
