#include "common.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"

s32 get_script_flag_mask();                             /* extern */
extern s16 scene_gate_script_flag;

/* Call clear_referenced_object_active_flag when the current check returns zero, then return one. */
s32 call_handler_when_check_clear(void) {
    if (get_script_flag_mask(scene_gate_script_flag) == 0) {
        clear_referenced_object_active_flag();
    }
    return 1;
}
