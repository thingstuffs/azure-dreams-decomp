#include "script_symbols.h"
#include "common.h"
#include "town/player/state.h"
#include "town/scene.h"
#include "town/scene/event.h"

/* Apply the object's flag when flag 0x145B is set, then process its action and handle failure. */
s32 process_selfy_tamago_entry(void *object, s32 actionParameter) {
    if (get_script_flag_mask(F_selfy_get_tamago) != 0) {
        set_script_flag_bit(*(s16 *)((u8 *)object + 0x18));
    }
    if (process_checked_entry(object, actionParameter) == 0) {
        invoke_callback_event_11();
        return 0;
    }
    return 1;
}
