#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player/state.h"
#include "town/scene/motion.h"
#include "town/data.h"

extern M2C_UNK D_80018EF4;
extern M2C_UNK D_80018F0C;

/* Selects data based on the 0xFB1 check and forwards it with the caller's parameters. */
void select_based_parameters(s32 callerValue, s32 unused, s32 callerData) {

    set_script_flag_bit(Ft_nyu);
    if (get_script_flag_mask(Fr_hospital_naoruru) == 0) {
        apply_entry_position(&D_80018EF4, &scene_request_context, callerValue, callerData);
    } else {
        apply_entry_position(&D_80018F0C, &scene_request_context, callerValue, callerData);
    }
}
