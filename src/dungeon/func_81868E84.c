#include "common.h"

typedef struct S_81868E84_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} S_81868E84_0;   /* temp_v0 in func_81868E84 */

typedef struct S_81868E84_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    void * unk_0C;
    s8 unk_10;
} S_81868E84_1;   /* temp_v0_2 in func_81868E84 */

typedef struct S_81868E84_2 {
    u8 pad_00[0x9];
    u8 unk_09;
} S_81868E84_2;   /* arg0 in func_81868E84 */

typedef struct S_81868E84_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81868E84_3;   /* arg1 in func_81868E84 */

typedef struct S_81868E84_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_81868E84_4;   /* temp_v0_3 in func_81868E84 */



extern void *func_8003FC64(s32);
extern u8 D_80024384[];

void func_81868E84(void *arg0, S_81868E84_3 *arg1) {
    u32 temp_a0;
    u16 temp_v1;
    u16 temp_v1_2;
    u16 temp_v1_3;
    void *temp_v0;
    S_81868E84_1 *temp_v0_2;
    S_81868E84_4 *temp_v0_3;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        ((S_81868E84_0 *)temp_v0)->unk_10 = D_80024384;
        temp_v0_2 = temp_v0 + 0x20;
        ((S_81868E84_0 *)temp_v0)->unk_20 = 0;
        temp_v0_2->unk_02 = 0;
        temp_a0 = ((S_81868E84_2 *)arg0)->unk_09;
        temp_v0_2->unk_06 = 0;
        temp_v0_2->unk_08 = 0;
        temp_v0_2->unk_0A = 0;
        temp_v0_2->unk_0C = arg0;
        temp_v0_2->unk_10 = 0x40;
        temp_v0_2->unk_04 = temp_a0;
        temp_v0_3 = ((S_81868E84_0 *)temp_v0)->unk_08;
        temp_v1 = arg1->unk_02;
        temp_v0_3->unk_0E = temp_v1;
        temp_v0_3->unk_02 = temp_v1;
        temp_v1_2 = arg1->unk_06;
        temp_v0_3->unk_12 = temp_v1_2;
        temp_v0_3->unk_06 = temp_v1_2;
        temp_v1_3 = arg1->unk_0A;
        temp_v0_3->unk_16 = temp_v1_3;
        temp_v0_3->unk_0A = temp_v1_3;
    }
}

/* MECHANISM: Hold arg0[9] in a u32 local after the first two zero stores.
   Its live range claims $a0, leaving the allocator result in $a1; u32 avoids
   the redundant andi and collapses the +1-word branch-displacement cascade. */
