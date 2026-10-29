#include "script_symbols.h"
#include "town/scene/entry_flag_queries.h"
#include "common.h"
#include "town/scene/flags.h"

extern void func_80018C74(s32);
extern void func_80018CEC(s32);
extern s32 func_80018D6C(s32);

/* Clear flags 0xFCB and 0xFCD; if 0x7D1 and 0xFD5 are set and 0x7D2 is clear, set flag 0x7D6 and return 1. */
s32 set_sbs24_pad04_if_ready(void)
{
    func_80018CEC(F_cheriru_first_cheriru);
    func_80018CEC(F_cheriru_first_nadia);
    if ((func_80018D6C(F_sbs24_top) != 0) &&
        (func_80018D6C(F_sbs24_pad00) == 0) &&
        (func_80018D6C(Fr_cheriru_pad28) != 0)) {
        func_80018C74(F_sbs24_pad04);
        return 1;
    }
    return 0;
}
