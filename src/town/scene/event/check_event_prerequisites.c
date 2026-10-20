#include "script_symbols.h"
#include "common.h"

extern s32 func_80018C74();
extern s32 func_80018CEC();
extern s32 func_80018D6C();

/* Runs the town event prerequisite checks and returns 1 when they trigger 0x7D4. */
s32 check_event_prerequisites(void) {
    func_80018CEC(F_cheriru_first_cheriru);
    func_80018CEC(F_cheriru_first_nadia);
    if (func_80018D6C(F_sbs24_top) != 0) {
        if (func_80018D6C(F_sbs24_pad00) == 0) {
            if (func_80018D6C(Fr_cheriru_scene08) != 0) {
                func_80018C74(F_sbs24_pad02);
                return 1;
            }
        }
    }
    return 0;
}
