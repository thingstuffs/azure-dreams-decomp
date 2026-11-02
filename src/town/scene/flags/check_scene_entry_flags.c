#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
#include "town/scene/flags.h"


/* Checks the entry and override flags before calling the handler. */
s32 check_scene_entry_flags(void *entry, s32 handler_arg) {
    s32 result;

    if (get_script_flag_mask(F_sbs11_pad34) != 0) {
        clear_script_flag_bit(F_sbs11_pad34);
        clear_script_flag_bit(F_sbs11_pad28);
        clear_script_flag_bit(F_sbs11_pad29);
        apply_selected_entry_values(entry, handler_arg);
        return 1;
    }

    if (get_script_flag_mask(*(s16 *)((u8 *)entry + 0x18)) == 0) {
        result = 0;
    } else {
        result = apply_selected_entry_values(entry, handler_arg) ^ 1;
    }
    return result;
}
