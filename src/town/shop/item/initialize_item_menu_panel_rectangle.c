#include "common.h"
#include "engine/texture.h"
#include "town/shop/item.h"

extern s32 D_800D15B8;

/* Initialize the record with global data and set its high flag bit. */
void initialize_item_menu_panel_rectangle(void *record) {
    texture_build_a_hex_48_byte_two_color_swapped_pattern_blocks_returns_base(record, &D_800D15B8);
    *(u8 *) ((u8 *) record + 0x3C) = *(u8 *) ((u8 *) record + 0x3C) | 0x80;
}
