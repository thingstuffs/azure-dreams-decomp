#include "common.h"

extern s8 spell_effect_selector_cache;

/* Stores -1 in spell_effect_selector_cache so the selection must be refreshed. */
void invalidate_spell_effect_selection(void) {
    spell_effect_selector_cache = -1;
}
