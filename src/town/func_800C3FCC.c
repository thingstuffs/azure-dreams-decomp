#include "common.h"
#include "m2c_compat.h"

s32 find_unflagged_node_by_key();                       /* extern */
M2C_UNK town_sd_sq_callagain();                            /* extern */
s32 apply_nearby_object_effects();                       /* extern */
extern M2C_UNK D_800C2074;
extern M2C_UNK D_800D4710;

/* Call town_sd_sq_callagain when either global object check returns zero. */
void retry_sound_sequence_when_ready(void) {
    if ((find_unflagged_node_by_key(&D_800C2074) == 0) || (apply_nearby_object_effects(&D_800D4710) == 0)) {
        town_sd_sq_callagain();
    }
}
