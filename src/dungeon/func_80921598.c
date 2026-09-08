#include "common.h"
#include "m2c_compat.h"
#define ARM_RRX(x, shift) (0)

extern u8 D_8008333C[];
extern s32 func_80033BC0();
extern u8 D_800E3548[];

typedef struct S_800F6598_0 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_800F6598_0;   /* temp_s1 in func_800F6598 */

typedef struct S_800F6598_1 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_1;   /* temp_v0 in func_800F6598 */

typedef struct S_800F6598_2 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_2;   /* temp_v0_2 in func_800F6598 */

typedef struct S_800F6598_3 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_3;   /* temp_v0_3 in func_800F6598 */

typedef struct S_800F6598_4 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_4;   /* temp_v0_4 in func_800F6598 */

typedef struct S_800F6598_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_5;   /* temp_v0_5 in func_800F6598 */

typedef struct S_800F6598_6 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_6;   /* temp_v0_6 in func_800F6598 */

typedef struct S_800F6598_7 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_7;   /* temp_v0_7 in func_800F6598 */

typedef struct S_800F6598_8 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_8;   /* temp_v0_8 in func_800F6598 */

typedef struct S_800F6598_9 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_9;   /* temp_v1_ptr in func_800F6598 */

s32 func_800F6598(void) {
    const s32 temp_a0_1 = 0x1F;
    const s32 temp_a0_2 = 0x20;
    const s32 temp_a0_3 = 0x21;
    register s32 temp_v1_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 temp_v0_value;
    u8 *temp_s1;
    s32 temp_s0;
    S_800F6598_1 *temp_v0;
    S_800F6598_2 *temp_v0_2;
    S_800F6598_3 *temp_v0_3;
    S_800F6598_4 *temp_v0_4;
    S_800F6598_5 *temp_v0_5;
    S_800F6598_6 *temp_v0_6;
    S_800F6598_7 *temp_v0_7;
    S_800F6598_8 *temp_v0_8;
    S_800F6598_9 *temp_v1_ptr;
    u8 *temp_early_ptr;
    s32 temp_return;

    /* D_8008333C is the pointer-bearing global itself; the old draft
     * accidentally added 0x333c twice. */
    temp_s1 = D_8008333C;
    temp_s0 = *(s32 *)temp_s1;
    if (func_80033BC0(0xA2) != 0) {
    temp_v1_value = ((S_800F6598_0 *)temp_s1)->unk_14;
    temp_v0 = ((temp_a0_1 << temp_v1_value) * 6) + temp_s0 + 0xBA;
    temp_v0->unk_04 = (u16)(temp_v0->unk_04 & 0x7FFF);
    temp_v1_value = ((S_800F6598_0 *)temp_s1)->unk_14;
    temp_v0_2 = ((temp_a0_1 << temp_v1_value) * 6) + temp_s0 + 0xC0;
    temp_v0_2->unk_04 = (u16)(temp_v0_2->unk_04 & 0x7FFF);
    temp_v0_value = ((S_800F6598_0 *)temp_s1)->unk_14;
    temp_v0_3 = ((temp_a0_1 << temp_v0_value) * 6) + temp_s0 + 0xC6;
    temp_v0_3->unk_04 = (u16)(temp_v0_3->unk_04 & 0x7FFF);
    temp_v1_value = ((S_800F6598_0 *)temp_s1)->unk_14;
    temp_v0_4 = ((temp_a0_2 << temp_v1_value) * 6) + temp_s0 + 0xBA;
    temp_v0_4->unk_04 = (u16)(temp_v0_4->unk_04 & 0x7FFF);
    temp_v1_value = ((S_800F6598_0 *)temp_s1)->unk_14;
    temp_v0_5 = ((temp_a0_2 << temp_v1_value) * 6) + temp_s0 + 0xC0;
    temp_v0_5->unk_04 = (u16)(temp_v0_5->unk_04 & 0x7FFF);
    temp_v0_value = ((S_800F6598_0 *)temp_s1)->unk_14;
    temp_v0_6 = ((temp_a0_2 << temp_v0_value) * 6) + temp_s0 + 0xC6;
    temp_v0_6->unk_04 = (u16)(temp_v0_6->unk_04 & 0x7FFF);
    temp_v1_value = ((S_800F6598_0 *)temp_s1)->unk_14;
    temp_v0_7 = ((temp_a0_3 << temp_v1_value) * 6) + temp_s0 + 0xBA;
    temp_v0_7->unk_04 = (u16)(temp_v0_7->unk_04 & 0x7FFF);
    temp_v1_value = ((S_800F6598_0 *)temp_s1)->unk_14;
    temp_v0_8 = ((temp_a0_3 << temp_v1_value) * 6) + temp_s0 + 0xC0;
    temp_v0_8->unk_04 = (u16)(temp_v0_8->unk_04 & 0x7FFF);
    temp_v0_value = ((S_800F6598_0 *)temp_s1)->unk_14;
    temp_v1_ptr = ((temp_a0_3 << temp_v0_value) * 6) + temp_s0 + 0xC6;
    temp_v1_ptr->unk_04 = (u16)(temp_v1_ptr->unk_04 & 0x7FFF);
    return 1;
    }
    temp_return = 0;
    temp_early_ptr = D_800E3548;
    temp_early_ptr[1] = 0;
    D_800E3548[0] = 0;
    return temp_return;
}
