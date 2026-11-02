#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/event.h"
#include "town/scene/hooks.h"

/* Stores the inputs and switches three scene flags according to the object's status test. */
s32 process_scene_status_actions(void *object, s32 value)
{
    set_global_entry_pair(object, value);
    if (get_script_flag_mask(*(s16 *)((u8 *)object + 0x18)) != 0) {
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
   store_supplied_values; explicit jump blocks preserve retail's nonzero-first layout.
   The two arms merge at one literal-zero epilogue, with no phantom tail call. */
