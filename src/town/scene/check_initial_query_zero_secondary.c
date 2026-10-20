#include "script_symbols.h"
#include "common.h"

extern s32 func_80018C74(s32);
extern s32 func_80018CEC(s32);
extern s32 func_80018D6C(s32);

// Updates event flags based on three prerequisite checks and reports whether they passed.
s32 check_initial_query_zero_secondary(void)
{
    if (func_80018D6C(F_sbs24_top) != 0 &&
        func_80018D6C(F_sbs24_pad00) == 0 &&
        func_80018D6C(F_cheriru_scene01) != 0) {
        func_80018C74(F_sbs24_pad06);
        return 1;
    }

    func_80018CEC(F_cheriru_first_cheriru);
    func_80018CEC(F_cheriru_first_nadia);
    return 0;
}
