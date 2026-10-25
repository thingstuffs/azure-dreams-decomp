#include "script_symbols.h"
#include "common.h"

s32 func_8001E578(s32, ...);
s32 func_8001E670(s32 flagIndex);                         /* extern */

/* Invoke func_8001E578 for 0x406 and 0x401 when the 0x406 check returns zero. */
void load_checked_event_resources(void) {
    if (func_8001E670(F_sbs01_pad17) == 0) {
        func_8001E578(F_sbs01_pad17);
        func_8001E578(F_sbs01_pad12);
    }
}
