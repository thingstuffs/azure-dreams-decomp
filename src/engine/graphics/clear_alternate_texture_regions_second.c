#include "common.h"

#include "common.h"

void clear_alternate_texture_regions(s16 use_alt_rect);
s32 load_town_sprite_bundle();                                /* extern */
extern s32 D_80080A80;

/* Save the result of func_80048D20 and transfer both image variants through the scratch buffer. */
void load_alternate_sprite_bundle_and_clear_textures(void) {
    D_80080A80 = load_town_sprite_bundle();
    clear_alternate_texture_regions(1);
    clear_alternate_texture_regions(0);
}
