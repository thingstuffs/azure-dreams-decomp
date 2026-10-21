#include "common.h"

extern s8 spell_effect_selector_cache;

/* Resets D_800DCF4D to -1. */
void invalidate_spell_effect_selection(void) {
    spell_effect_selector_cache = -1;
}
