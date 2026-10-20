#include "common.h"

#include "common.h"

void load_alternate_sprite_bundle_and_clear_textures(void);
void init_town_runtime_objects(void);
void town_se_reserve(s16 effect_id, s16 sound_id);

/* Invoke operation 0xD with -1, then run the two runtime routines. */
void init_town_runtime_with_sound_effect(void) {
    town_se_reserve(0xD, -1);
    load_alternate_sprite_bundle_and_clear_textures();
    init_town_runtime_objects();
}
