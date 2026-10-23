#include "common.h"
#include "frontend/card.h"
void func_8003D548(s32);                     /* extern */
void func_80400EF8(void);                            /* extern */
extern s8 card_dev_effect_mode;

/* Set the global mode to 2 and invoke the transition routines. */
void card_dev_start_default_screen(void) {
    card_dev_effect_mode = 2;
    func_80400EF8();
    func_8003D548(3);
}
