#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene/event.h"
#include "town/player/state.h"



extern s8 D_8001ABF9;

/* Selects event data when flag conditions match, otherwise clears two event flags. */
s32 select_event_data_or_clear_flags(void) {
    if ((get_script_flag_mask(F_sbs24_top) != 0) &&
        (get_script_flag_mask(F_sbs24_pad00) == 0) &&
        (get_script_flag_mask(F_cheriru_scene02_0) != 0)) {
        set_script_flag_bit(F_sbs24_pad07);
        town_scene_root->position->unk_40 =
            &D_8001ABF9;
        return 1;
    }
    clear_script_flag_bit(F_cheriru_first_cheriru);
    clear_script_flag_bit(F_cheriru_first_nadia);
    return 0;
}
