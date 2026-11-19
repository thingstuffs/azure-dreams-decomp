#include "frontend/card/slot_details.h"
#include "common.h"

extern void *build_drawing(void *, s32, s32);
extern u8 D_800841DC[], D_8008423C[], D_8008429C[];
/* Builds the menu drawing and assigns screen positions and sources to its four entries. */
void initialize_menu_item_positions(CardDevSlotDetails *work) {
    u8 *storage = work->border_packets;
    CardDevMenuEntry *item;
    build_drawing(storage, 0xF8, 0x48);
    item = work->entries[3];
    item->display.block->fields.x = 0xA0; item->display.block->fields.y = 0xB0; item->display.payload.data = storage;
    item = work->entries[0];
    item->display.block->fields.x = 0x60; item->display.block->fields.y = 0x88; item->display.payload.data = D_800841DC;
    item = work->entries[1];
    item->display.block->fields.x = 0xD0; item->display.block->fields.y = 0x88; item->display.payload.data = D_8008423C;
    item = work->entries[2];
    item->display.block->fields.x = 0x20; item->display.block->fields.y = 0x88; item->display.payload.data = D_8008429C;
}
