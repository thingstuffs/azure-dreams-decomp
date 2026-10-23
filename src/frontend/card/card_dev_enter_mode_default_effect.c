#include "common.h"
#include "frontend/card.h"

extern u8 card_dev_effect_mode;
extern void func_80400E34(void);
typedef struct { u8 pad[0x10]; void *callback; } Effect;
extern Effect *allocate_or_reuse_effect_and_install_callback(void *, void *);
/*
 * Sets card_dev_effect_mode to one, runs func_80400E34, and creates or reuses the effect with
 * selector 0.
 */
void card_dev_enter_mode_default_effect(void *owner) {
    card_dev_effect_mode = 1;
    func_80400E34();
    allocate_or_reuse_effect_and_install_callback(owner, (void *)0);
}
