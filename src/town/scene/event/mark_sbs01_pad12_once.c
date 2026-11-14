#include "town/player/state.h"
#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"


/* Invoke func_8001E578 for 0x406 and 0x401 when the 0x406 check returns zero. */
void mark_sbs01_pad12_once(void) {
    if (get_script_flag_mask(F_sbs01_pad17) == 0) {
        set_script_flag_bit(F_sbs01_pad17);
        set_script_flag_bit(F_sbs01_pad12);
    }
}
