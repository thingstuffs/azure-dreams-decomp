#include "script_symbols.h"
#include "common.h"

extern s32 func_80018964(s32);

/* Return whether both checks for 0x1200 and 0x1201 return zero. */
s32 check_town_event_flags_clear(void) {
    s32 result;
    s32 return_value;

    if (func_80018964(Fp_bibian_pool_event) == 0) {
        result = func_80018964(Fp_mia_pool_event);
        return_value = 1;
        if (result == 0) {
            return return_value;
        }
    }
    return_value = 0;
    return return_value;
}

/* MECHANISM: The call-shaped body naturally gives the 0x18 frame with only ra saved. */
