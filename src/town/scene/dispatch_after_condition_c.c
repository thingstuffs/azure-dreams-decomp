#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene.h"
#include "town/scene/flags.h"

#include "town/scene/record_actions.h"

/* Run the preliminary callback for condition 0x12C4, then dispatch the argument pair. */
void dispatch_after_condition_12_c_4(Rec_func_800165F4_arg0 *dispatch_value, s32 dispatch_option) {
    if (get_script_flag_mask(F_set_mascot1) != 0) {
        set_current_entry_script_flag();
    }
    apply_selected_entry_values(dispatch_value, dispatch_option);
}
