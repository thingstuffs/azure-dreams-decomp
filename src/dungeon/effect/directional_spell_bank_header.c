#include "dungeon/effect/spell_effect.h"

/* Selector 4 uses the updater entry at the first word of its bank. */
const struct {
    void (*entry)(struct DirectionalSpell *, ObjectPosition *, SpriteFrameState *);
} directional_spell_bank_header = {
    update_directional_spell_sprites,
};
