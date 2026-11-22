#include "common.h"
#include "town/devkit.h"
#include "frontend/card/server_imports.h"
#include "frontend/card.h"

/* Set the global flag, prepare state, and process the target in mode 1. */
void start_card_dev_slot_screen_mode_one(struct ObjectNodeHeader *request) {
    card_dev_effect_mode = 1;
    card_dev_init();
    create_card_dev_slot_screen_effect(request, 1);
}
