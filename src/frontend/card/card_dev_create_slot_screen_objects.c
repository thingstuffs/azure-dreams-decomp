#include "common.h"
#include "frontend/card/menu.h"
#include "frontend/card.h"

typedef struct { u8 pad[0x10]; void *callback; u8 pad14[0x2C]; void *first, *second; } Owner;
extern void func_80400948(void);

/*
 * Creates the card background and slot objects, saves their handles, runs the screen setup, and
 * installs card_boot_handle_menu_selection_input.
 */
void card_dev_create_slot_screen_objects(u8 *work) {
    Owner *owner = (Owner *)(work - 0x20);
    *(s32 *)(work + 0x20) = init_card_background_object((s32)owner, (s32)(work + 0xC));
    *(void **)(work + 0x24) = init_card_slot_object((s32)owner);
    func_80400948();
    owner->callback = card_boot_handle_menu_selection_input;
}
