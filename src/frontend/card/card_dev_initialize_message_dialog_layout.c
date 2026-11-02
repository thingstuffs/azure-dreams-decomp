#include "common.h"
#include "frontend/card/server_imports.h"

/*
 * Devkit-server build of card_boot_initialize_message_dialog_layout: binds the record, lays out its render
 * templates (+0x67C, from the blocks at +0x654 and +0x664) and builds the dialog packets.
 */
void card_dev_initialize_message_dialog_layout(u8 *record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20)
{
    func_80402EA4(record, value_14, entry_index, value_0c, value_20);
    func_80402974(record + 0x67C, record + 0x654, record + 0x664);
    func_80402D90(record);
}
