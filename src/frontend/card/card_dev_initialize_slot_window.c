#include "common.h"
#include "frontend/card/slot_marker.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"

/*
 * Devkit-server build of card_boot_initialize_slot_window: the same three steps on the server's smaller slot
 * record (frame block at +0x1C8, primary display block at +0x1A0, position words at +0x1B0).
 */
void card_dev_initialize_slot_window(CardDevMenu10 *window, struct ObjectNodeHeader *owner, s32 slot_index)
{
    card_dev_set_slot_index_and_owner(window, owner, slot_index);
    func_80403DA0(&window->frame, &window->frame_block, window->frame_position, slot_index);
    layout_slot_window_entries(window);
}
