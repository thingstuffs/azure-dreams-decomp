#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"


/* Returns whether the query for 0x5C0 yields zero. */
s32 is_script_flag_sbs11_pad29_clear(void) {
    return get_script_flag_mask(F_sbs11_pad29) == 0;
}
