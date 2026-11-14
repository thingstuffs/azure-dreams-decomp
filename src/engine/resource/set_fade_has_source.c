#include "common.h"

#include "engine/effect.h"
#include "engine/resource.h"

/* Marks the fade manager as having a source when its sprite has one. */
void set_fade_has_source(FadeManagerBody *dest, SpriteFrameState *source) {
    if (source->source != 0) {
        dest->has_source = 1;
    }
}
