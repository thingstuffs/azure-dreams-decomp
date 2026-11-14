#include "common.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"
#include "town/player.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "town/data.h"

/* Call clear_referenced_object_active_flag when the current check returns zero, then return one. */
s32 clear_object_unless_gate_flag_set(void) {
    if (get_script_flag_mask(scene_gate_script_flag) == 0) {
        clear_referenced_object_active_flag();
    }
    return 1;
}
