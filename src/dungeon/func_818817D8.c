#include "common.h"

typedef struct S_80024FD8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80024FD8_0;   /* temp_v0 in func_80024FD8 */

typedef struct S_80024FD8_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024FD8_1;   /* temp_v1 in func_80024FD8 */

typedef struct S_80024FD8_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024FD8_2;   /* arg0 in func_80024FD8 */

typedef struct S_80024FD8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x4];
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    s16 unk_1E;
} S_80024FD8_3;   /* temp_s0 in func_80024FD8 */

typedef struct S_80024FD8_4 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x8];
    s16 unk_1E;
    u8 pad_20[0x4];
    s16 unk_24;
} S_80024FD8_4;   /* temp_v1_2 in func_80024FD8 */



extern void *func_8003FC64();
extern void func_8004491C();
extern void func_8003DB94();

extern u8 D_80024EE0[];
extern u8 D_80025854[];
extern u8 D_80045C34[];
extern u16 D_800257CC;

void *func_80024FD8(S_80024FD8_2 *arg0, s16 arg1, s16 arg2)
{
    s32 temp_a0;
    s32 value;
    u16 counter;
    S_80024FD8_3 *temp_s0;
    void *temp_v0;
    S_80024FD8_1 *temp_v1;
    S_80024FD8_4 *temp_v1_2;

    temp_v0 = func_8003FC64(0x202);
    if (temp_v0 != 0) {
        ((S_80024FD8_0 *)temp_v0)->unk_10 = D_80024EE0;
        func_8004491C(temp_v0, D_80045C34);
        temp_v1 = ((S_80024FD8_0 *)temp_v0)->unk_08;
        temp_v1->unk_02 = arg0->unk_02;
        temp_v1->unk_06 = arg0->unk_06;
        temp_v1->unk_0A = arg0->unk_0A;
        temp_s0 = ((S_80024FD8_0 *)temp_v0)->unk_0C;
        temp_s0->unk_0C = 0x808080;
        temp_s0->unk_1C = 0x400;
        temp_s0->unk_1E = 0x1CCC;
        func_8003DB94(temp_s0, D_80025854, 0);
        temp_a0 = (s16)arg2;
        temp_s0->unk_18 = (temp_a0 << 8) - 0x400;
        value = 0x60;
        ASM_KEEP(value);   /* MATCH pin: load-bearing for the whole function shape */
        temp_v1_2 = (u8 *)temp_v0 + 0x20;
        ASM_KEEP(temp_v1_2);   /* MATCH pin: load-bearing for the whole function shape */
        temp_s0->unk_10 = value;
        counter = D_800257CC;
        temp_s0->unk_16 = 0x400;
        temp_v1_2->unk_24 = arg2;
        temp_v1_2->unk_14 = arg1;
        temp_v1_2->unk_1E = temp_a0 * 2;
        D_800257CC = counter + 1;
    }
    return temp_v0;
}

/* MECHANISM: Natural argument liveness preserves the retail 0x28 frame and s0-s4 save contract.
   The guarded a0/v1 roles share one signed arg2 conversion and hold the three-store destination base.
   An unpinned 0x60 local plus ordered keeps yields the exact li/addiu/lui/sh/lhu counter schedule. */
