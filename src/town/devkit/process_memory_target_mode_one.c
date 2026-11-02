#include "common.h"
void card_dev_init(void);                            /* extern */
#include "town/devkit.h"
typedef struct { u8 pad[0x10]; void *callback; } Effect;
Effect * allocate_or_reuse_effect_and_install_callback(void *first, void *second);                /* extern */
extern s8 card_dev_effect_mode;

/* Set the global flag, prepare state, and process the target in mode 1. */
void process_memory_target_mode_one(s32 target) {
    card_dev_effect_mode = 1;
    card_dev_init();
    allocate_or_reuse_effect_and_install_callback(target, 1);
}
