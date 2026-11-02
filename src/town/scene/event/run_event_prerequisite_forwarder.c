#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"
#include "town/player/state.h"
#include "town/scene/motion.h"

extern s32 D_80018DFC;
extern s32 scene_state_dispatch_context;

/* Run func_80018C74, then forward the inputs if either queried condition is nonzero. */
s32 run_event_prerequisite_forwarder(s32 primary_input, s32 unused, s32 secondary_input)
{
    set_script_flag_bit(F_s24_door_open);
    if ((get_script_flag_mask(Ft_name_to_cheril) == 0) &&
        (get_script_flag_mask(F_cheriru_first_nadia2) == 0)) {
        return 0;
    }
    return apply_entry_position(&D_80018DFC, &scene_state_dispatch_context, primary_input, secondary_input);
}
