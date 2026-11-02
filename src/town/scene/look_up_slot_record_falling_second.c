#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/player/state.h"


typedef void (*Callback)(s32, s32);

/* Updates event state and checks completion conditions, invoking a callback if unmet. */
s32 look_up_slot_record_falling(void)
{
    clear_script_flag_bit(F_hos_first_cheriru);
    clear_script_flag_bit(F_hos_first_hush);

    if (get_script_flag_mask(F_sbs16_top) != 0 &&
        get_script_flag_mask(F_sbs16_pad00) == 0 &&
        get_script_flag_mask(Fr_hospital_scene06) != 0) {
        set_script_flag_bit(F_sbs16_pad03);
        return 1;
    }

    ((Callback)town_scene_root->services->callback_2F8)(0x10, 0x200);
    return 0;
}
