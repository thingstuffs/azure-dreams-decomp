#include "common.h"

extern s8 spell_effect_selector_cache;

/* Resets D_800DCF4D to -1. */
void func_8092184C(void) {
    spell_effect_selector_cache = -1;
}
