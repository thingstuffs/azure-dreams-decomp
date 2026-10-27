#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"


/* Checks the entry and override flags before calling the handler. */
s32 check_scene_entry_flags(void *entry, s32 handler_arg) {
    s32 result;

    if (func_80018B5C(F_sbs11_pad34) != 0) {
        func_80018ADC(F_sbs11_pad34);
        func_80018ADC(F_sbs11_pad28);
        func_80018ADC(F_sbs11_pad29);
        func_80017D80(entry, handler_arg);
        return 1;
    }

    if (func_80018B5C(*(s16 *)((u8 *)entry + 0x18)) == 0) {
        result = 0;
    } else {
        result = func_80017D80(entry, handler_arg) ^ 1;
    }
    return result;
}
