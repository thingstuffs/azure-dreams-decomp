#include "dungeon/system/submit_control_and_reset_status.h"
#include "common.h"
#include "dungeon/effect/sprite.h"

/* Stores -1 in spell_effect_selector_cache so the selection must be refreshed. */
void invalidate_spell_effect_selection(void) {
    spell_effect_selector_cache = -1;
}
