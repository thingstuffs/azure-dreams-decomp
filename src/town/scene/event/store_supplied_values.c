#include "script_symbols.h"
#include "town/scene.h"
#include "town/scene/hooks.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/event.h"

extern s16 scene_request_flag_id;

/* Conditionally processes 0x50C, then forwards the inputs to both shared routines. */
void store_scene_values_after_flag_check(s32 value, s32 data) {
    if (get_script_flag_mask(F_sbs07_pad21) != 0) {
        if (get_script_flag_mask(scene_request_flag_id) == 0) {
            clear_script_flag_bit(F_sbs07_pad21);
        }
    }
    set_global_entry_pair(value, data);
    process_checked_entry(value, data);
}
