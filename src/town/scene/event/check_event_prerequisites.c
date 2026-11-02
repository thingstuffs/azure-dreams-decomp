#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"
#include "town/player/state.h"

/* Runs the town event prerequisite checks and returns 1 when they trigger 0x7D4. */
s32 check_event_prerequisites(void) {
    clear_script_flag_bit(F_cheriru_first_cheriru);
    clear_script_flag_bit(F_cheriru_first_nadia);
    if (get_script_flag_mask(F_sbs24_top) != 0) {
        if (get_script_flag_mask(F_sbs24_pad00) == 0) {
            if (get_script_flag_mask(Fr_cheriru_scene08) != 0) {
                set_script_flag_bit(F_sbs24_pad02);
                return 1;
            }
        }
    }
    return 0;
}
