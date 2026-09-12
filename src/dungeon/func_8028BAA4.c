#include "common.h"

typedef struct S_8001EAA4_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_8001EAA4_0;   /* group_saved + ((var_a1 + var_a2) * 4) in func_8001EAA4 */

typedef struct S_8001EAA4_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_8001EAA4_1;   /* temp_a3 in func_8001EAA4 */



extern s32 func_800A6D30(s8 *, s8 *, s32, s32);
extern s32 D_80012090[];
extern s16 D_8001F6F8[];
extern u8 D_80073414[];

/* Selects a random item by category thresholds and eligible item weights. */
s32 func_8001EAA4(s8 *category_out, s8 *item_out, s32 arg2, s32 arg3) {
    s32 category_index;
    s32 rarity;
    s32 category_scale_or_weight;
    u8 *table_cursor_or_item_offset;
    s32 item_index;
    s32 scan_value;
    register u16 *category_threshold ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 item_flags;
    register s32 cumulative_weight ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 result_index;
    u32 rng_result;
    u16 random_weight;
    unsigned long table_base_or_mode;
    register u8 *item_category_table ASM_REG("$11");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 *category_entry ASM_REG("$13");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    rng_result = func_800A6D30(category_out, item_out, arg2, arg3);
    category_threshold = (u16 *)D_8001F6F8;
    random_weight = category_threshold[19];
    random_weight = (rng_result & 0xFFFF) % random_weight;
    category_index = 1;
    table_cursor_or_item_offset = (u8 *)category_threshold;
    category_threshold = (u16 *)(table_cursor_or_item_offset + 2);
    category_scale_or_weight = random_weight & 0xFFFF;
loop_1:
    item_index = 1;
    if (*category_threshold < (u32)category_scale_or_weight) {
        category_index += 1;
        category_threshold += 1;
        if (category_index >= 0x13) {
            ASM_UNDEF(item_index);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            item_index = 1;
        } else {
            goto loop_1;
        }
    }
    category_scale_or_weight = category_index * 4;
    category_threshold = &((u16 *)table_cursor_or_item_offset)[category_index];
    table_base_or_mode = (unsigned long)D_80073414;
    scan_value = category_scale_or_weight + category_index;
    scan_value *= 4;
    table_cursor_or_item_offset = (u8 *)(scan_value + table_base_or_mode);
    cumulative_weight = category_threshold[-1];
    scan_value = table_cursor_or_item_offset[2];
    if (item_index < scan_value) {
        scan_value = category_index << 16;
        item_category_table = (u8 *)table_base_or_mode;
        table_base_or_mode = 2;
        category_entry = table_cursor_or_item_offset;
        ASM_KEEP_NV(category_entry);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        result_index = scan_value >> 16;
        table_cursor_or_item_offset = (u8 *)0x14;
loop_6:
        item_flags = *(u16 *)(table_cursor_or_item_offset + ((S_8001EAA4_0 *)(item_category_table + ((category_scale_or_weight + category_index) * 4)))->unk_0C);
        if (!(item_flags & 0x10)) {
            if (item_flags & 0x40) {
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                category_scale_or_weight = category_index * 4;
                if (D_80012090[0] != (s32)table_base_or_mode) {
                    goto block_19;
                }
            }
            {
                scan_value = *(u16 *)(table_cursor_or_item_offset + ((S_8001EAA4_1 *)category_entry)->unk_0C) & 0x3000;
                if (scan_value < 0) {
                    scan_value += 0xFFF;
                }
                rarity = (scan_value >> 0xC) & 3;
                category_scale_or_weight = 0x80;
                if (rarity != 0) {
                    category_scale_or_weight = 0x55;
                    if (rarity != 1) {
                        category_scale_or_weight = 1;
                        if (rarity == (s32)table_base_or_mode) {
                            category_scale_or_weight = 0x20;
                        }
                    }
                }
                cumulative_weight += category_scale_or_weight;
                if (random_weight < (u32)(cumulative_weight & 0xFFFF)) {
                    *category_out = (s8)category_index;
                    *item_out = (s8)item_index;
                    return result_index;
                }
                goto block_18;
            }
        }
block_18:
        category_scale_or_weight = category_index * 4;
block_19:
        scan_value = item_category_table[((category_scale_or_weight + category_index) * 4) + 2];
        item_index += 1;
        table_cursor_or_item_offset += 0x14;
        if (item_index >= scan_value) {
            *category_out = 0;
            *item_out = 0;
            return 0;
        }
        goto loop_6;
    }
    *category_out = 0;
    *item_out = 0;
    return 0;
}
