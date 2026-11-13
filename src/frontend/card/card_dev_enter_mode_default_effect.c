#include "common.h"
#include "frontend/card.h"

#include "frontend/card/effect_mode_data.h"
typedef struct { u8 pad[0x10]; void *callback; } Effect;
extern Effect *create_card_dev_slot_screen_effect(void *, void *);
/*
 * Sets card_dev_effect_mode to one, runs card_dev_init, and creates or reuses the effect with
 * selector 0.
 */
void card_dev_enter_mode_default_effect(void *owner) {
    card_dev_effect_mode = 1;
    card_dev_init();
    create_card_dev_slot_screen_effect(owner, 0);
}
