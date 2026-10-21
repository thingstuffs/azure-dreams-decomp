#include "common.h"

#include "common.h"
#include "engine/graphics.h"
#include "engine/town.h"
void plt_init_sleep_set(void);                            /* extern */

/* Runs the three runtime routines in sequence. */
void init_town_runtime_sleep(void) {
    load_alternate_sprite_bundle_and_clear_textures();
    init_town_runtime_objects();
    plt_init_sleep_set();
}
