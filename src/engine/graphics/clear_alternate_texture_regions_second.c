#include "common.h"

#include "common.h"
#include "engine/graphics.h"
#include "slus.h"
#include "slus/data.h"

/* Save the result of func_80048D20 and transfer both image variants through the scratch buffer. */
void load_alternate_sprite_bundle_and_clear_textures(void) {
    loaded_sprite_bundle_attributes = load_town_sprite_bundle();
    clear_alternate_texture_regions(1);
    clear_alternate_texture_regions(0);
}
