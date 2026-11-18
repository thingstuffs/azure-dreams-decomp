#include "common.h"
#include "town/devkit.h"
#include "frontend/card/server_imports.h"
#include "frontend/card.h"

/* Set the global flag, prepare state, and process the target in mode 0. */
void start_card_dev_slot_screen_mode_zero(s32 target) {
    card_dev_effect_mode = 1;
    card_dev_init();
    create_card_dev_slot_screen_effect(target, 0);
}
