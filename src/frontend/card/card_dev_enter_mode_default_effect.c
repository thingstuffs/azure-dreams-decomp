#include "common.h"
#include "frontend/card.h"

extern u8 card_dev_effect_mode;
typedef struct { u8 pad[0x10]; void *callback; } Effect;
extern Effect *allocate_or_reuse_effect_and_install_callback(void *, void *);
/*
 * Sets card_dev_effect_mode to one, runs card_dev_init, and creates or reuses the effect with
 * selector 0.
 */
void card_dev_enter_mode_default_effect(void *owner) {
    card_dev_effect_mode = 1;
    card_dev_init();
    allocate_or_reuse_effect_and_install_callback(owner, 0);
}
