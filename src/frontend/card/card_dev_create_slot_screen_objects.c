#include "common.h"
#include "frontend/card/menu.h"
#include "frontend/card.h"

typedef struct CardDevSlotScreenBody {
    u8 pad_00[0xC];
    s32 selection_flag;
    u8 pad_10[0x10];
    void *background;
    void *slots;
} CardDevSlotScreenBody;

/*
 * Creates the card background and slot objects, saves their handles, runs the screen setup, and
 * installs card_boot_handle_menu_selection_input.
 */
void card_dev_create_slot_screen_objects(CardDevSlotScreenBody *work) {
    ObjectNodeHeader *owner = NODE_HEADER(work);
    work->background = init_card_background_object(owner, &work->selection_flag);
    work->slots = init_card_slot_object((s32)owner);
    toggle_card_selection_state();
    owner->update_callback = card_boot_handle_menu_selection_input;
}
