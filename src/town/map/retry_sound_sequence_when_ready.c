#include "common.h"
#include "m2c_compat.h"

s32 find_unflagged_node_by_key();                       /* extern */
#include "town/map/sound_sequence_replay_g00650.h"
s32 apply_nearby_object_effects();                       /* extern */
extern void map_active_node_key();
extern M2C_UNK map_active_callbacks;

/* Call town_sd_sq_callagain when either global object check returns zero. */
void retry_sound_sequence_when_ready(void) {
    if ((find_unflagged_node_by_key(&map_active_node_key) == 0) || (apply_nearby_object_effects(&map_active_callbacks) == 0)) {
        town_sd_sq_callagain();
    }
}
