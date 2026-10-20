#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"



extern s8 D_8001ABF9;

extern void func_80018C74(s32);
extern void func_80018CEC(s32);
extern s32 func_80018D6C(s32);

/* Selects event data when flag conditions match, otherwise clears two event flags. */
s32 select_event_data_or_clear_flags(void) {
    if ((func_80018D6C(F_sbs24_top) != 0) &&
        (func_80018D6C(F_sbs24_pad00) == 0) &&
        (func_80018D6C(F_cheriru_scene02_0) != 0)) {
        func_80018C74(F_sbs24_pad07);
        ((TownPositionState *)D_80016000->unk_1C)->unk_40 =
            &D_8001ABF9;
        return 1;
    }
    func_80018CEC(F_cheriru_first_cheriru);
    func_80018CEC(F_cheriru_first_nadia);
    return 0;
}
