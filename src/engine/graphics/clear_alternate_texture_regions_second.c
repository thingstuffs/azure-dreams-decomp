#include "common.h"

#include "common.h"
#include "engine/graphics.h"
#include "slus.h"
#include "slus/data.h"

/* Caches the town sprite bundle attributes, then transfers both alternate texture variants. */
void load_alternate_sprite_bundle_and_clear_textures(void) {
    loaded_sprite_bundle_attributes = load_town_sprite_bundle();
    clear_alternate_texture_regions(1);
    clear_alternate_texture_regions(0);
}
