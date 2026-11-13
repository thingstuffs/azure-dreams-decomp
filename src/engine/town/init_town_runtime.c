#include "common.h"

#include "engine/graphics.h"
#include "engine/town.h"

/* Runs the two Konami runtime routines in sequence. */
void init_town_runtime(void) {
    load_town_sprite_bundle_and_clear_alternates();
    init_town_runtime_objects();
}
