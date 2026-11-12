#include "common.h"
#include "town/devkit.h"
typedef struct { u8 pad[0x10]; void *callback; } Effect;
Effect * allocate_or_reuse_effect_and_install_callback(void *first, void *second);                /* extern */
#include "frontend/card/effect_mode_data.h"
#include "frontend/card.h"

/* Set the global flag, prepare state, and process the target in mode 1. */
void process_memory_target_mode_one(s32 target) {
    card_dev_effect_mode = 1;
    card_dev_init();
    allocate_or_reuse_effect_and_install_callback(target, 1);
}
