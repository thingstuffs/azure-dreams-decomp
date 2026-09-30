#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

typedef struct S_8009D6F4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8009D6F4_1;   /* ((((row << shift) + col) * 6) + table) in func_8009D6F4 */


typedef struct {
    u32 word[2];
} __attribute__((packed)) Copy8;

extern u8 D_800E50A8[];
extern void func_800672D8(Copy8 *, u8 *);
extern Copy8 D_80088CB0;
extern u8 D_800EA000[];

typedef struct S_8009D6F4_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
} S_8009D6F4_0;   /* temp_t1 in func_8009D6F4 */

/* Refresh nonzero packed grid nibbles from clamped table values, then pass on the saved data. */
void func_8009D6F4(void) {
    Copy8 saved_data;
    Copy8 *data_source;
    register u8 *base;
    u8 *cursor;
    u8 *state;
    u8 *grid_dims;
    register u8 *table;
    s32 first_col;
    s32 dimension_unit;
    s16 next_row;
    s16 row_index;
    s32 row;
    u8 packed_output;
    u8 packed_input;

    data_source = &D_80088CB0;
    saved_data = *data_source;
    packed_input = 0;
    base = D_800E50A8;
    cursor = base;
    row_index = 0;
    state = ((u8 *)(&gameWork));
    grid_dims = state + 0x1DC;
    if ((1 << ((S_8009D6F4_0 *)grid_dims)->unk_16) > 0) {
        s32 col_index;
        s32 nibble_mask;
        s32 next_col;

        first_col = 0;
        dimension_unit = 1;
        table = D_800EA000;
        do {
            col_index = 0;
            if (first_col < (dimension_unit << ((S_8009D6F4_0 *)grid_dims)->unk_14)) {
                nibble_mask = row_index << 16;
                row = nibble_mask >> 16;
                do {
                    nibble_mask = col_index & 1;
                    if (nibble_mask == 0) {
                        packed_input = *cursor;
                        *cursor = 0;
                        nibble_mask = packed_input & 0xF;
                    } else {
                        nibble_mask = packed_input & 0xF0;
                    }
                    if (nibble_mask != 0) {
                        s32 value_bits;
                        s32 value_bits_2;
                        s32 level;
                        s16 clamped_level;
                        s32 col;
                        register s16 shift;

                        col = (s16) col_index;
                        shift = ((S_8009D6F4_0 *)grid_dims)->unk_14;
                        value_bits_2 = (s16) (((S_8009D6F4_1 *)(((((row << shift) + col) * 6) + table)))->unk_02 + 0x200) / 64;
                        clamped_level = value_bits_2;
                        level = value_bits_2;
                        if (level >= 0x10) {
                            clamped_level = 15;
                        } else {
                            if (level <= 0) {
                                clamped_level = 1;
                            }
                        }
                        value_bits = clamped_level << 0x10;
                        level = value_bits >> 0x10;
                        packed_output = *cursor;
                        if (col_index & 1) {
                            value_bits = packed_output | (level << 4);
                        } else {
                            value_bits = packed_output | level;
                        }
                        *cursor = value_bits;
                    }
                    if (col_index & 1) {
                        next_col = col_index + 1;
                        cursor += 1;
                        col_index = next_col;
                    } else {
                        next_col = col_index + 1;
                        col_index = next_col;
                    }
                } while ((s16) next_col < (dimension_unit << ((S_8009D6F4_0 *)grid_dims)->unk_14));
            }
            next_row = row_index + 1;
            row_index = next_row;
        } while (next_row < (dimension_unit << ((S_8009D6F4_0 *)grid_dims)->unk_16));
    }
    func_800672D8(&saved_data, base);
}
