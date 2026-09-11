#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009D6F4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8009D6F4_1;   /* ((((row << shift) + col) * 6) + table) in func_8009D6F4 */




typedef struct {
    u32 word[2];
} __attribute__((packed)) Copy8;

extern u8 D_800E50A8[];
extern u8 D_80083160[];
M2C_UNK func_800672D8(Copy8 *);
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
    register u8 *cursor ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *state;
    u8 *grid_dims;
    register u8 *table;
    s32 first_col;
    s32 dimension_unit;
    s16 next_row;
    register s16 row_index ASM_REG("$11");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 row ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 packed_output;
    u8 packed_input;

    data_source = &D_80088CB0;
    saved_data = *data_source;
    packed_input = 0;
    base = D_800E50A8;
    cursor = base;
    ASM_KEEP(base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    state = D_80083160;
    grid_dims = state + 0x1DC;
    if ((1 << ((S_8009D6F4_0 *)grid_dims)->unk_16) > 0) {
        register s32 col_index ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 nibble_mask;
        register s32 row_wide ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 next_col ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        row_index = 0;
        first_col = 0;
        dimension_unit = 1;
        table = D_800EA000;
row_loop:
        ASM_KEEP(base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        col_index = 0;
        if (first_col < (dimension_unit << ((S_8009D6F4_0 *)grid_dims)->unk_14)) {
            row_wide = row_index << 16;
            row = row_wide >> 16;
col_loop:
            nibble_mask = col_index & 1;
            if (nibble_mask == 0) {
                packed_input = *cursor;
                *cursor = 0;
                nibble_mask = packed_input & 0xF;
            } else {
                nibble_mask = packed_input & 0xF0;
            }
            if (nibble_mask != 0) {
                register s32 value_bits ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                s32 level;
                s16 clamped_level;
                s32 col;
                register s16 shift;

                col = (s16) col_index;
                shift = ((S_8009D6F4_0 *)grid_dims)->unk_14;
                value_bits = (s16) (((S_8009D6F4_1 *)(((((row << shift) + col) * 6) + table)))->unk_02 + 0x200) / 64;
                clamped_level = value_bits;
                do {
                    level = value_bits;
                } while (0);
                if (level >= 0x10) {
                    clamped_level = 15;
                    goto clamp_value;
                }
                if (level <= 0) {
                    clamped_level = 1;
                }
clamp_value:
                value_bits = clamped_level << 0x10;
                level = value_bits >> 0x10;
                packed_output = *cursor;
                if (col_index & 1) {
                    value_bits = packed_output | (level << 4);
                    goto store_value;
                }
                value_bits = packed_output | level;
store_value:
                *cursor = value_bits;
                goto advance_col;
            }
advance_col:
            if (col_index & 1) {
                next_col = col_index + 1;
                cursor += 1;
            } else {
                next_col = col_index + 1;
            }
            do {
                col_index = next_col;
            } while (0);
            if ((s16) next_col >= (dimension_unit << ((S_8009D6F4_0 *)grid_dims)->unk_14)) {
                goto advance_row;
            }
            goto col_loop;
        }
advance_row:
        next_row = row_index + 1;
        row_index = next_row;
        if (next_row >= (dimension_unit << ((S_8009D6F4_0 *)grid_dims)->unk_16)) {
            goto done;
        }
        goto row_loop;
    }
done:
    func_800672D8(&saved_data);
}
