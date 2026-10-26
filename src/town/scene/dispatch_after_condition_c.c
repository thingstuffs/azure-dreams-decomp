#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

extern void set_current_entry_script_flag(void);
extern void apply_selected_entry_values(s32 record, s32 entry_index);

/* Run the preliminary callback for condition 0x12C4, then dispatch the argument pair. */
void dispatch_after_condition_12_c_4(s32 dispatch_value, s32 dispatch_option) {
    if (get_script_flag_mask(F_set_mascot1) != 0) {
        set_current_entry_script_flag();
    }
    apply_selected_entry_values(dispatch_value, dispatch_option);
}
