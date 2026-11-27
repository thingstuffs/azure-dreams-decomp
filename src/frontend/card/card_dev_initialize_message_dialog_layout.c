#include "frontend/card/message_display.h"
#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"

/*
 * Devkit-server build of card_boot_initialize_message_dialog_layout: binds the record, lays out its render
 * templates (+0x67C, from the blocks at +0x654 and +0x664) and builds the dialog packets.
 */
void card_dev_initialize_message_dialog_layout(CardDevDialogDisplay *record, struct ObjectNodeHeader *owner, s32 entry_index, s32 value_0c, s32 *result_slot)
{
    func_80402EA4(record, owner, entry_index, value_0c, result_slot);
    func_80402974(&record->template_node, &record->primary, &record->secondary);
    init_dialog_object(record);
}
