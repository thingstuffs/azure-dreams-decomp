#include "common.h"
#include "town/devkit.h"

typedef struct { u8 pad[0x10]; void *callback; } Effect;

Effect *create_card_dev_slot_screen_effect(void *first, void *second);
#include "frontend/card/effect_mode_data.h"
#include "frontend/card.h"

/* Set the global flag, prepare state, and process the target in mode 0. */
void process_memory_target_mode_zero(s32 target) {
    card_dev_effect_mode = 1;
    card_dev_init();
    create_card_dev_slot_screen_effect(target, 0);
}
