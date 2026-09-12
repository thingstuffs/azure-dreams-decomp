#include "common.h"

typedef struct {
    s32 word0 __attribute__((packed));
    s32 word4 __attribute__((packed));
} PackedPair;

typedef struct {
    u8 pad0[0x14];
    s16 field_14;
    s16 field_16;
} DungeonConfig;

extern PackedPair D_80088CB0;
extern u8 D_80083160[];
extern u8 D_800E50A8[];
extern u8 D_800EA000[];

extern void func_800672D8(PackedPair *, u8 *);
extern void func_8009BF7C(s32, s32);

/* Pack dungeon cell height levels into nibbles and submit the buffer. */
void func_8009D8A4(void) {
    PackedPair upload_pair;
    DungeonConfig *config;
    u8 *dungeon_data;
    u8 *buffer;
    u8 *write_ptr;
    u8 *cells;
    u8 *cell;
    s32 zero;
    s32 one;
    s16 row;
    s32 column;
    s16 next_row;
    register s32 row_offset ASM_REG("$3");
    s32 level;
    u16 cell_type;
    s32 packed_levels;
    u8 packed_empty;
    register s32 value ASM_REG("$2");

    upload_pair = D_80088CB0;
    buffer = D_800E50A8;
    write_ptr = buffer;
    ASM_KEEP(write_ptr);
    dungeon_data = D_80083160;
    config = (DungeonConfig *)(dungeon_data + 0x1DC);
    if ((1 << config->field_16) > 0) {
        row = 0;
        zero = 0;
        one = 1;
        cells = D_800EA000;
next_row_loop:
        column = 0;
        {
            s16 width_shift = config->field_14;
            u16 stride_shift;
            register s32 row_index ASM_REG("$8");
            stride_shift = *(volatile u16 *)((u8 *)config + 0x14);
            if (!(zero < (one << width_shift))) {
                goto row_done;
            }
            value = (u32) row << 16;
            row_index = value >> 16;
            row_offset = row_index << stride_shift;
next_cell:
            cell = (u8 *)((long)((row_offset + (s16) column) * 6) + (long)cells);
            cell_type = *(u16 *)cell;
            if ((cell_type != 0) && (cell_type != 3)) {
                register u16 clamped_level ASM_REG("$4");
                s16 raw_level;

                value = (s16) (*(u16 *)(cell + 2) + 0x200) / 64;
                clamped_level = value;
                raw_level = value;
                if (raw_level >= 0x10) {
                    clamped_level = 15;
                } else if (raw_level <= 0) {
                    clamped_level = 1;
                }
                value = (u32) clamped_level << 16;
                level = value >> 16;
                packed_levels = *write_ptr;
                if ((s32) column & 1) {
                    value = packed_levels | (level << 4);
                } else {
                    value = packed_levels | level;
                }
            } else {
                register s32 odd_column;

                packed_empty = *write_ptr;
                odd_column = column & 1;
                if (odd_column) {
                    value = packed_empty & 0xF;
                } else {
                    value = packed_empty & 0xF0;
                }
            }
            *write_ptr = value;
            {
                s32 odd_column;
                odd_column = column & 1;
                if (odd_column) {
                    write_ptr += 1;
                }
                value = column + 1;
            }
            column = value;
            ASM_KEEP_NV(value);
            value = (s16) value;
            width_shift = config->field_14;
            stride_shift = *(volatile u16 *)((u8 *)config + 0x14);
            if (value >= (one << width_shift)) {
                goto row_done;
            }
            row_offset = row_index << stride_shift;
            goto next_cell;
        }
row_done:
        next_row = row + 1;
        row = next_row;
        if (row < (one << config->field_16)) {
            goto next_row_loop;
        }
    }
    func_800672D8(&upload_pair, buffer);
    func_8009BF7C(1, 0x20);
}
