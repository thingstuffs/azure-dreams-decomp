#include "script_symbols.h"
#include "common.h"
#include "town/scene/flags.h"

extern void func_80018C74(s32);
extern void func_80018CEC(s32);
extern s32 func_80018D6C(s32);

/* If flag 0xFB1 is set, set flag 0xFD3 and return 1; otherwise clear flags 0xFCB and 0xFCD and return 0. */
s32 set_flag_0xfd3_when_flag_0xfb1_set(void)
{
    if (func_80018D6C(Fr_hospital_naoruru) != 0) {
        func_80018C74(F_chriru_mode_home);
        return 1;
    }
    func_80018CEC(F_cheriru_first_cheriru);
    func_80018CEC(F_cheriru_first_nadia);
    return 0;
}
