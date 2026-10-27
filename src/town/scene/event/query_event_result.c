#include "script_symbols.h"
#include "common.h"
#include "town/scene/position_entries.h"

extern ScenePositionEntry D_80018E2C;
extern s32 scene_state_dispatch_context;

s32 func_80018D6C(s32 flagIndex);

// Returns func_800182E4's result when func_80018D6C(0xFDD) is nonzero, otherwise zero.
s32 query_event_result(void *firstInput, s32 unusedInput, s32 secondInput) {
    s32 result;

    if (func_80018D6C(F_oyako_genka) != 0) {
        result = func_800182E4(&D_80018E2C, &scene_state_dispatch_context, firstInput, secondInput);
    } else {
        result = 0;
    }
    return result;
}
