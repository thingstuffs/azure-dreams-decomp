#include "script_symbols.h"
#include "common.h"
#include "town/scene/state_data.h"
#include "town/scene/position_entries.h"
#include "town/scene/event.h"
#include "town/player/state.h"

extern ScenePositionEntry D_80018E2C;

// Returns func_800182E4's result when func_80018D6C(0xFDD) is nonzero, otherwise zero.
s32 select_response_if_oyako_genka(void *firstInput, s32 unusedInput, s32 secondInput) {
    s32 result;

    if (get_script_flag_mask(F_oyako_genka) != 0) {
        result = apply_entry_position(&D_80018E2C, &scene_state_dispatch_context, firstInput, secondInput);
    } else {
        result = 0;
    }
    return result;
}
