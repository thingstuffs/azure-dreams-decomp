#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "engine/runtime.h"
#define ARM_RRX(x, shift) (0)


typedef struct S_800F6598_1 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_1;

typedef struct S_800F6598_2 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_2;

typedef struct S_800F6598_3 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_3;

typedef struct S_800F6598_4 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_4;

typedef struct S_800F6598_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_5;

typedef struct S_800F6598_6 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_6;

typedef struct S_800F6598_7 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_7;

typedef struct S_800F6598_8 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_8;

typedef struct S_800F6598_9 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800F6598_9;

/* Clear bit 15 in the 3x3 grid region when flag 0xA2 is set; otherwise reset the state bytes. */
s32 clear_center_tile_flags_when_enabled(void) {
    const s32 row_before = 0x1F;
    const s32 row_center = 0x20;
    const s32 row_after = 0x21;
    s32 row_shift;
    s32 last_col_shift;
    MapGrid *grid_state;
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

    grid_state = &g_game_work.map;
    grid_base = ((s32)grid_state->cells);
    if (test_resident_bit(0xA2) != 0) {
        row_shift = grid_state->shiftX;
        row_shift = row_before << row_shift;
        cell_31_31 = (row_shift * 6) + grid_base + 0xBA;
        cell_31_31->unk_04 = (u16)(cell_31_31->unk_04 & 0x7FFF);
        row_shift = grid_state->shiftX;
        row_shift = row_before << row_shift;
        cell_31_32 = (row_shift * 6) + grid_base + 0xC0;
        cell_31_32->unk_04 = (u16)(cell_31_32->unk_04 & 0x7FFF);
        last_col_shift = grid_state->shiftX;
        cell_31_33 = ((row_before << last_col_shift) * 6) + grid_base + 0xC6;
        cell_31_33->unk_04 = (u16)(cell_31_33->unk_04 & 0x7FFF);
        row_shift = grid_state->shiftX;
        row_shift = row_center << row_shift;
        cell_32_31 = (row_shift * 6) + grid_base + 0xBA;
        cell_32_31->unk_04 = (u16)(cell_32_31->unk_04 & 0x7FFF);
        row_shift = grid_state->shiftX;
        row_shift = row_center << row_shift;
        cell_32_32 = (row_shift * 6) + grid_base + 0xC0;
        cell_32_32->unk_04 = (u16)(cell_32_32->unk_04 & 0x7FFF);
        last_col_shift = grid_state->shiftX;
        cell_32_33 = ((row_center << last_col_shift) * 6) + grid_base + 0xC6;
        cell_32_33->unk_04 = (u16)(cell_32_33->unk_04 & 0x7FFF);
        row_shift = grid_state->shiftX;
        row_shift = row_after << row_shift;
        cell_33_31 = (row_shift * 6) + grid_base + 0xBA;
        cell_33_31->unk_04 = (u16)(cell_33_31->unk_04 & 0x7FFF);
        row_shift = grid_state->shiftX;
        row_shift = row_after << row_shift;
        cell_33_32 = (row_shift * 6) + grid_base + 0xC0;
        cell_33_32->unk_04 = (u16)(cell_33_32->unk_04 & 0x7FFF);
        last_col_shift = grid_state->shiftX;
        cell_33_33 = ((row_after << last_col_shift) * 6) + grid_base + 0xC6;
        cell_33_33->unk_04 = (u16)(cell_33_33->unk_04 & 0x7FFF);
        return 1;
    }
    result = 0;
    reset_state = ((u8 *)dungeon_ground_items);
    reset_state[1] = 0;
    dungeon_ground_items->unk_00 = 0;
    return result;
}
