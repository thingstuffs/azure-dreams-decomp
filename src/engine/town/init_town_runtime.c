#include "common.h"

#include "common.h"

void load_alternate_sprite_bundle_and_clear_textures(void);
void init_town_runtime_objects(void);

/* Runs the two Konami runtime routines in sequence. */
void init_town_runtime(void) {
    load_alternate_sprite_bundle_and_clear_textures();
    init_town_runtime_objects();
}
