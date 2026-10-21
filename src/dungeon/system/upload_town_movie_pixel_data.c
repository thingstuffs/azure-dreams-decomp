#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void upload_town_movie_pixel_data(); /* extern */
extern s32 map_scene_selector_alias;
extern M2C_UNK D_800FC428;

/* Calls upload_town_movie_pixel_data with the global buffer when the state is 0x13000C. */
void upload_town_movie_pixel_data_2(void) {
    if (map_scene_selector_alias == 0x13000C) {
        upload_town_movie_pixel_data(0x360, 0x100, 0x20, 0x80, &D_800FC428);
    }
}
