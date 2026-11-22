#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"

/*
 * Sets card_dev_effect_mode to one, runs card_dev_init, and creates or reuses the effect with
 * selector 2.
 */
void card_dev_enter_mode_second_effect(struct ObjectNodeHeader *request) {
    card_dev_effect_mode = 1;
    card_dev_init();
    create_card_dev_slot_screen_effect(request, 2);
}
