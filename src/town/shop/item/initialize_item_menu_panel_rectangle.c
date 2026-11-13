#include "common.h"
#include "engine/texture.h"
#include "town/shop/item.h"

extern s32 D_800D15B8;

/* Initialize the record with global data and set its high flag bit. */
void initialize_item_menu_panel_rectangle(void *record) {
    build_panel_rectangle_packets(record, &D_800D15B8);
    *((u8 *) record + 0x3C) = *((u8 *) record + 0x3C) | 0x80;
}
