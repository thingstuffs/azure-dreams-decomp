#include "common.h"
#include "town/scene.h"
#include "town/player.h"

extern s32 scene_update_state;

/* Set state 1 and return whether the initial check passes and the count is at least 20. */
s32 set_state_one_and_check_count(void) {
    scene_update_state = 1;
    if (count_enabled_town_entries() != 0) {
        if (get_linked_record_field_2_d_60() >= 20) {
            return 1;
        }
    }
    return 0;
}
