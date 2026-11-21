#include "script_symbols.h"
#include "town/player/script_flags.h"
#include "town/scene/position_entries.h"

extern ScenePositionEntry D_80017ED4[];
extern ScenePositionEntry D_80017EDC[];
extern ScenePositionEntry D_80017EE4[];
extern u8 D_80017FA8[];

s32 resolve_hospital_entry_by_flags(void *context, s32 unused, s32 selection) {
    if (get_script_flag_mask(F_shospital_first)) {
        if (get_script_flag_mask(F_shospital_build)) {
            return apply_entry_position(D_80017EE4, D_80017FA8, context, selection);
        }
        if (get_script_flag_mask(Fr_shospital_01)) {
            return apply_entry_position(D_80017EDC, D_80017FA8, context, selection);
        }
        if (!get_script_flag_mask(F_shospital_first_hush) &&
            get_script_flag_mask(F_sbs15_top) && !get_script_flag_mask(F_sbs15_pad00)) {
            return apply_entry_position(D_80017EDC, D_80017FA8, context, selection);
        }
    }
    return apply_entry_position(D_80017ED4, D_80017FA8, context, selection);
}
