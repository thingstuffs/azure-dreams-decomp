#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80026978_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80026978_0;   /* temp_v0 in func_80026978 */

typedef struct S_80026978_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
} S_80026978_1;   /* arg0 in func_80026978 */

typedef struct S_80026978_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_80026978_2;   /* temp_s2 in func_80026978 */

typedef struct S_80026978_3 {
    u8 pad_00[0xE];
    s16 unk_0E;
} S_80026978_3;   /* temp_v1 in func_80026978 */

typedef struct S_80026978_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80026978_4;   /* temp_s0 in func_80026978 */



extern void *func_8003FC64();
extern void func_8004491C();
extern s32 rand();
extern u8 D_80026B00[];
extern u8 D_80045340[];
extern u8 D_800F7944[];

void func_80026978(S_80026978_1 *arg0)
{
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_v0_2;
    s32 color;
    S_80026978_4 *temp_s0;
    S_80026978_2 *temp_s2;
    S_80026978_3 *temp_v1;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x136);
    if (temp_v0 != NULL) {
        ((S_80026978_0 *)temp_v0)->unk_10 = D_80026B00;
        func_8004491C(temp_v0, D_80045340);
        temp_s2 = ((S_80026978_0 *)temp_v0)->unk_08;
        temp_s0 = ((S_80026978_0 *)temp_v0)->unk_0C;
        temp_a0 = (arg0->unk_02 + (rand() % 40)) - 0x14;
        temp_s2->unk_02 = temp_a0;
        temp_a0_2 = (arg0->unk_06 + (rand(temp_a0) % 40)) - 0x14;
        temp_s2->unk_06 = temp_a0_2;
        temp_a0_3 = (arg0->unk_0A + (rand(temp_a0_2) % 40)) - 0x14;
        temp_s2->unk_0A = temp_a0_3;
        temp_s2->unk_0C = arg0->unk_0C;
        temp_v0_2 = rand(temp_a0_3);
        color = 0x808080;
        temp_v0_2 = ((temp_v0_2 & 0x1FF) - 0x100) << 0xA;
        ASM_KEEP(temp_v0_2);   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_v1 = (u8 *)temp_v0 + 0x20;
        temp_s2->unk_14 = temp_v0_2;
        ASM_KEEP(temp_v1);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        temp_v1->unk_0E = 3;
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
        temp_s0->unk_08 = D_800F7944;
        temp_s0->unk_04 = 0;
        temp_s0->unk_05 = 0;
        temp_s0->unk_0C = color;
        temp_s0->unk_14 = temp_s0->unk_14 | 0xC;
    }
}
