#include "common.h"

typedef struct S_81876014_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x36];
    void * unk_44;
    void * unk_48;
    void * unk_4C;
    u16 unk_50;
    s16 unk_52;
    u16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    u16 unk_60;
    u16 unk_62;
    s16 unk_64;
    s16 unk_66;
} S_81876014_0;   /* arg0 in func_81876014 */

typedef struct S_81876014_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x90];
    s16 unk_9C;
} S_81876014_1;   /* temp_s3 in func_81876014 */

typedef struct S_81876014_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_81876014_2;   /* arg1 in func_81876014 */

typedef struct S_81876014_3 {
    s32 unk_00;
} S_81876014_3;   /* temp_v1_data in func_81876014 */

typedef struct S_81876014_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_81876014_4;   /* arg2 in func_81876014 */

typedef struct S_81876014_5 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_81876014_5;   /* ((S_81876014_0 *)arg0)->unk_44 in func_81876014 */

typedef struct S_81876014_6 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_81876014_6;   /* ((S_81876014_0 *)arg0)->unk_48 in func_81876014 */



extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s16 D_80026664;
extern s32 D_800814A0;

void func_81876014(void *arg0, void *arg1, void *arg2) {
    s16 temp_a0;
    register s16 temp_a1 ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    register s16 temp_a2 ASM_REG("$6");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    u16 temp_v0_field;
    register u16 temp_v1_base ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    register s16 temp_v1_field64 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    void *temp_v1_data;
    register s32 temp_v0_3 ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    u16 temp_v0_tail;
    s16 temp_v0_4;
    s32 temp_v0;
    s32 temp_product;
    u16 temp_v1;
    void *temp_s3;

    temp_s3 = ((S_81876014_0 *)arg0)->unk_4C;
    D_80026664 = 1;
    if (((S_81876014_1 *)temp_s3)->unk_9C == 0x37) {
        ((S_81876014_0 *)arg0)->unk_50 =
            (u16)((((S_81876014_0 *)arg0)->unk_0A *
                   func_80064584(((S_81876014_0 *)arg0)->unk_0C)) >> 12);
        temp_v0 = func_800644B8(((S_81876014_0 *)arg0)->unk_0C);
        temp_product = ((S_81876014_0 *)arg0)->unk_0A * temp_v0;
        ((S_81876014_0 *)arg0)->unk_60 = 0;
        temp_a0 = (*(volatile u16 *)((u8 *)arg0 + 0x60));
        temp_v0_field = ((S_81876014_0 *)arg0)->unk_50;
        ASM_KEEP(temp_v0_field);   /* MATCH pin: keeps a statement from moving across a call/branch */
        ((S_81876014_0 *)arg0)->unk_62 = temp_a0;
        ASM_KEEP(temp_v0_field);   /* MATCH pin: keeps a statement from moving across a call/branch */
        temp_v1_base = temp_v0_field;
        temp_v0_field += 0x10;
        ASM_KEEP(temp_v0_field);   /* MATCH pin: keeps a statement from moving across a call/branch */
        ((S_81876014_0 *)arg0)->unk_52 = temp_v0_field;
        temp_v0_field = temp_v1_base;
        ((S_81876014_0 *)arg0)->unk_54 = temp_v1_base;
        ASM_KEEP(temp_v1_base);   /* MATCH pin: retail register colouring depends on it */
        temp_v1_field64 = temp_a0;
        ASM_KEEP(temp_v1_field64);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        temp_v1_field64 += 0x10;
        ((S_81876014_0 *)arg0)->unk_64 = temp_v1_field64;
        temp_v0_field += 0x10;
        ((S_81876014_0 *)arg0)->unk_56 = temp_v0_field;
        temp_v1_data = ((S_81876014_0 *)arg0)->unk_44;
        ASM_KEEP(temp_v1_data);   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_v0_3 = temp_product >> 12;
        ((S_81876014_0 *)arg0)->unk_58 = temp_v0_3;
        ASM_KEEP(temp_v0_3);   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_a0 = temp_v0_3;
        ASM_KEEP(temp_a0);   /* MATCH pin: retail register colouring depends on it */
        temp_a1 = temp_v0_3;
        ASM_KEEP(temp_a1);   /* MATCH pin: retail register colouring depends on it */
        temp_a2 = temp_v0_3;
        ASM_KEEP(temp_a2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        temp_v0_tail = ((S_81876014_0 *)arg0)->unk_60;
        ((S_81876014_0 *)arg0)->unk_5A = temp_a0;
        ((S_81876014_0 *)arg0)->unk_5C = temp_a1;
        ((S_81876014_0 *)arg0)->unk_5E = temp_a2;
        temp_v0_tail += 0x10;
        ((S_81876014_0 *)arg0)->unk_66 = temp_v0_tail;
        ((S_81876014_2 *)arg1)->unk_00 = ((S_81876014_3 *)temp_v1_data)->unk_00;
        ((S_81876014_2 *)arg1)->unk_04 = ((S_81876014_5 *)(((S_81876014_0 *)arg0)->unk_44))->unk_04;
        ((S_81876014_2 *)arg1)->unk_08 = ((S_81876014_5 *)(((S_81876014_0 *)arg0)->unk_44))->unk_08;
        ((S_81876014_4 *)arg2)->unk_0C = ((S_81876014_6 *)(((S_81876014_0 *)arg0)->unk_48))->unk_0C;
        ((S_81876014_4 *)arg2)->unk_0D = ((S_81876014_6 *)(((S_81876014_0 *)arg0)->unk_48))->unk_0D;
        ((S_81876014_4 *)arg2)->unk_0E = ((S_81876014_6 *)(((S_81876014_0 *)arg0)->unk_48))->unk_0E;
        temp_v1 = ((S_81876014_0 *)arg0)->unk_0C;
        temp_v0_4 = temp_v1 - 0x64;
        ((S_81876014_0 *)arg0)->unk_0C = temp_v0_4;
        if (temp_v0_4 < 0) {
            ((S_81876014_0 *)arg0)->unk_0C = temp_v1 + 0xF9C;
        }
        if (((S_81876014_1 *)temp_s3)->unk_0A >= 5) {
            goto block_4;
        }
    } else {
block_4:
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
