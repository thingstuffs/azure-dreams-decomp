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

/* Clear bit 15 in the 3x3 grid region when flag 0xA2 is set; otherwise reset the state bytes. */
s32 func_800F6598(void) {
    const s32 row_before = 0x1F;
    const s32 row_center = 0x20;
    const s32 row_after = 0x21;
    register s32 row_shift ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 last_col_shift;
    u8 *grid_state;
    s32 grid_base;
    S_800F6598_1 *cell_31_31;
    S_800F6598_2 *cell_31_32;
    S_800F6598_3 *cell_31_33;
    S_800F6598_4 *cell_32_31;
    S_800F6598_5 *cell_32_32;
    S_800F6598_6 *cell_32_33;
    S_800F6598_7 *cell_33_31;
    S_800F6598_8 *cell_33_32;
    S_800F6598_9 *cell_33_33;
    u8 *reset_state;
    s32 result;

    grid_state = D_8008333C;
    grid_base = *(s32 *)grid_state;
    if (func_80033BC0(0xA2) != 0) {
        row_shift = ((S_800F6598_0 *)grid_state)->unk_14;
        cell_31_31 = ((row_before << row_shift) * 6) + grid_base + 0xBA;
        cell_31_31->unk_04 = (u16)(cell_31_31->unk_04 & 0x7FFF);
        row_shift = ((S_800F6598_0 *)grid_state)->unk_14;
        cell_31_32 = ((row_before << row_shift) * 6) + grid_base + 0xC0;
        cell_31_32->unk_04 = (u16)(cell_31_32->unk_04 & 0x7FFF);
        last_col_shift = ((S_800F6598_0 *)grid_state)->unk_14;
        cell_31_33 = ((row_before << last_col_shift) * 6) + grid_base + 0xC6;
        cell_31_33->unk_04 = (u16)(cell_31_33->unk_04 & 0x7FFF);
        row_shift = ((S_800F6598_0 *)grid_state)->unk_14;
        cell_32_31 = ((row_center << row_shift) * 6) + grid_base + 0xBA;
        cell_32_31->unk_04 = (u16)(cell_32_31->unk_04 & 0x7FFF);
        row_shift = ((S_800F6598_0 *)grid_state)->unk_14;
        cell_32_32 = ((row_center << row_shift) * 6) + grid_base + 0xC0;
        cell_32_32->unk_04 = (u16)(cell_32_32->unk_04 & 0x7FFF);
        last_col_shift = ((S_800F6598_0 *)grid_state)->unk_14;
        cell_32_33 = ((row_center << last_col_shift) * 6) + grid_base + 0xC6;
        cell_32_33->unk_04 = (u16)(cell_32_33->unk_04 & 0x7FFF);
        row_shift = ((S_800F6598_0 *)grid_state)->unk_14;
        cell_33_31 = ((row_after << row_shift) * 6) + grid_base + 0xBA;
        cell_33_31->unk_04 = (u16)(cell_33_31->unk_04 & 0x7FFF);
        row_shift = ((S_800F6598_0 *)grid_state)->unk_14;
        cell_33_32 = ((row_after << row_shift) * 6) + grid_base + 0xC0;
        cell_33_32->unk_04 = (u16)(cell_33_32->unk_04 & 0x7FFF);
        last_col_shift = ((S_800F6598_0 *)grid_state)->unk_14;
        cell_33_33 = ((row_after << last_col_shift) * 6) + grid_base + 0xC6;
        cell_33_33->unk_04 = (u16)(cell_33_33->unk_04 & 0x7FFF);
        return 1;
    }
    result = 0;
    reset_state = D_800E3548;
    reset_state[1] = 0;
    D_800E3548[0] = 0;
    return result;
}
