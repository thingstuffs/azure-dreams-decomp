#include "shared/sprite_frame_state.h"
#include "dungeon/effect/sprite/linked_object_chain.h"

/* Select one of the 16 transform frames for this sprite. */
void set_sprite_animation_entry(SpriteFrameState *sprite, s16 entry_index) {
    LinkedSpriteSource *source = sprite->source;
    sprite->frame_entry = &source->frames[entry_index];
}
