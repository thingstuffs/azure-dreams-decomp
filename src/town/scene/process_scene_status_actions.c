#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/event.h"
#include "town/scene/hooks.h"
#include "town/scene.h"

/* Save the selected choice and switch the scene flags according to the row flag. */
s32 process_scene_status_actions(TownObjectSet *row, s32 entry_index)
{
    set_global_entry_pair(row, entry_index);
    if (get_script_flag_mask(row->entry_flag) != 0) {
        clear_script_flag_bit(F_sbs07_pad28);
        set_script_flag_bit(F_sbs07_pad27);
        set_script_flag_bit(F_sbs07_pad23);
    } else {
        invoke_callback_event_11();
        set_script_flag_bit(F_sbs07_pad28);
        clear_script_flag_bit(F_sbs07_pad27);
        clear_script_flag_bit(F_sbs07_pad23);
    }
    return 0;
}

/* MECHANISM: A 24-byte frame holds arg0 in the sole saved register s0 across
   set_global_entry_pair; explicit jump blocks preserve retail's nonzero-first layout.
   The two arms merge at one literal-zero epilogue, with no phantom tail call. */
