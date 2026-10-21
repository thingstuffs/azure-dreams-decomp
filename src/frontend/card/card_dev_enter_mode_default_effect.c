#include "common.h"
#include "frontend/card.h"

extern u8 D_8008CA34;
extern void func_80400E34(void);
typedef struct { u8 pad[0x10]; void *callback; } Effect;
extern Effect *allocate_or_reuse_effect_and_install_callback(void *, void *);
void card_dev_enter_mode_default_effect(void *owner) {
    D_8008CA34 = 1;
    func_80400E34();
    allocate_or_reuse_effect_and_install_callback(owner, (void *)0);
}
