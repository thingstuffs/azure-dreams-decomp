#include "common.h"
#include "town/map/resource.h"

extern s16 town_pending_sound[2];

/* town_se_reserve: reserve the town sound effect pair. */
void town_se_reserve(s16 effect_id, s16 sound_id) {
    town_pending_sound[0] = effect_id;
    town_pending_sound[1] = sound_id;
}
