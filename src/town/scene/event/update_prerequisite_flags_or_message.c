#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/event.h"
#include "shared/town_root.h"
#include "town/player/state.h"
#include "town.h"

/* Update event flags when prerequisites are met, otherwise invoke the fallback callback. */
s32 update_prerequisite_flags_or_message(void) {
    set_script_flag_sbs32_pad34();
    if (town_pair_table_has_first(6) != 0) {
        set_script_flag_bit(F_sbs32_pad16);
    }
    if (town_pair_table_has_first(0xB) != 0) {
        set_script_flag_bit(F_sbs32_pad17);
    }
    if (get_script_flag_mask(F_sbs32_pad16) != 0 && get_script_flag_mask(F_sbs32_pad32) != 0) {
        set_script_flag_bit(F_sbs32_pad18);
        return 1;
    }
    if (get_script_flag_mask(F_sbs32_pad17) != 0 && get_script_flag_mask(F_sbs32_pad30) != 0) {
        set_script_flag_bit(F_sbs32_pad18);
        set_script_flag_bit(F_sbs32_pad28);
        set_script_flag_bit(F_sbs32_pad29);
        return 1;
    }
    {
        s8 *context = (s8 *)town_scene_root;
        s8 *callback_table = *(s8 **)(context + 0x20);
        s32 (*fallback_fn)(s32, s32) = *(s32 (**)(s32, s32))(callback_table + 0x2F8);
        fallback_fn(0xF, 0x200);
    }
    return 0;
}
