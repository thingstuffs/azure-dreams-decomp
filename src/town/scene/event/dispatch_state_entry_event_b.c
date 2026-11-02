#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/player/state.h"

typedef void (*Callback)(s32, s32);




/* Runs the conditional action or invokes the fallback callback. */
s32 dispatch_state_entry_event_8(void) {
    Rec_D_80016000 *callback_owner;

    clear_script_flag_bit(F_hos_first_cheriru);
    clear_script_flag_bit(F_hos_first_hush);

    if (get_script_flag_mask(F_sbs16_top) != 0) {
        if (get_script_flag_mask(F_sbs16_pad00) == 0) {
            set_script_flag_bit(F_sbs16_pad04);
            return 1;
        }
    }
    callback_owner = town_scene_root;
    ((Callback)callback_owner->services->callback_2F8)(0x10, 0x200);
    return 0;
}
