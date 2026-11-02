#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"

s32 set_script_flag_bit(s32, ...);
s32 get_script_flag_mask(s32 flagIndex);                         /* extern */

/* Invoke func_8001E578 for 0x406 and 0x401 when the 0x406 check returns zero. */
void load_checked_event_resources(void) {
    if (get_script_flag_mask(F_sbs01_pad17) == 0) {
        set_script_flag_bit(F_sbs01_pad17);
        set_script_flag_bit(F_sbs01_pad12);
    }
}
