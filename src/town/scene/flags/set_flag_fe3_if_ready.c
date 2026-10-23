#include "script_symbols.h"
#include "town/scene/entry_flag_queries.h"
#include "common.h"

extern void func_80018C74(s32);
extern void func_80018CEC(s32);
extern s32 func_80018D6C(s32);

/* Checks event prerequisites and updates the corresponding event flags. */
s32 set_taiin_if_ready(void)
{
    if ((func_80018D6C(F_sbs24_top) != 0) &&
        (func_80018D6C(F_sbs24_pad00) == 0) &&
        (func_80018D6C(Fr_hospital_scene07_2) != 0) &&
        ((func_80018D6C(F_sbs16_top) == 0) ||
         (func_80018D6C(Ft_tai) != 0))) {
        func_80018C74(F_taiin);
        return 1;
    }

    func_80018CEC(F_cheriru_first_cheriru);
    func_80018CEC(F_cheriru_first_nadia);
    return 0;
}
