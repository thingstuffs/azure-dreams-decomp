#include "common.h"

extern s32 texture_build_a_hex_48_byte_two_color_swapped_pattern_blocks_returns_base(s32, s32*);
extern s32 initialize_shop_display_records(s32, s32*);
extern s32 D_800D15C4;

/* Process the record and its subrecord at offset 0x48 using the shared data. */
void process_shop_record_and_subrecord(s32 record_address) {
    texture_build_a_hex_48_byte_two_color_swapped_pattern_blocks_returns_base(record_address, &D_800D15C4);
    initialize_shop_display_records(record_address + 0x48, &D_800D15C4);
}
