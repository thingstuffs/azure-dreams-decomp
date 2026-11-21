#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"

/*
 * Devkit-server build of card_boot_initialize_slot_window: the same three steps on the server's smaller slot
 * record (frame block at +0x1C8, primary display block at +0x1A0, position words at +0x1B0).
 */
void card_dev_initialize_slot_window(u8 *record, struct ObjectNodeHeader *owner, s32 slot_index)
{
    card_dev_set_slot_index_and_owner(record, owner, slot_index);
    func_80403DA0(record + 0x1C8, record + 0x1A0, record + 0x1B0, slot_index);
    layout_slot_window_entries(record);
}
