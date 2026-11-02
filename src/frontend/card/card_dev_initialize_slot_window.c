#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"

/*
 * Devkit-server build of card_boot_initialize_slot_window: the same three steps on the server's smaller slot
 * record (frame block at +0x1C8, primary display block at +0x1A0, position words at +0x1B0).
 */
void card_dev_initialize_slot_window(u8 *record, s32 setup_value, s32 processing_value)
{
    func_80404308(record, setup_value, processing_value);
    func_80403DA0(record + 0x1C8, record + 0x1A0, record + 0x1B0, processing_value);
    complete_pending_object_state(record);
}
