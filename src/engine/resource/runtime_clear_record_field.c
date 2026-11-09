#include "common.h"

#include "common.h"
#include "engine/effect.h"
#include "engine/resource.h"

/* Clears the fade manager's has_source flag when its fade ends. */
void runtime_clear_record_field_04(FadeManagerBody *state, SpriteFrameState *unused_sprite) {
    state->has_source = 0;
}
