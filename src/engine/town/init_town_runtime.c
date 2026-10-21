#include "common.h"

#include "common.h"
#include "engine/graphics.h"
#include "engine/town.h"

/* Runs the two Konami runtime routines in sequence. */
void init_town_runtime(void) {
    load_alternate_sprite_bundle_and_clear_textures();
    init_town_runtime_objects();
}
