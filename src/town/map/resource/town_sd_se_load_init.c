#include "common.h"
#include "town/map/resource.h"

extern s16 town_saved_sound[];
extern s16 town_pending_sound[];
extern s8 scene_music_hold[];

/* town_sd_se_load_init: Reset both sound-effect load slot arrays and clear the shared flag. */
void town_sd_se_load_init(void) {
    s16 *load_slots;

    town_saved_sound[0] = -1;
    load_slots = town_saved_sound;
    load_slots[1] = -1;
    load_slots[2] = -1;
    load_slots[3] = -1;

    town_pending_sound[0] = -1;
    load_slots = town_pending_sound;
    load_slots[1] = -1;
    load_slots[2] = -1;
    load_slots[3] = -1;

    scene_music_hold[0] = 0;
}
