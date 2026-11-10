#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"


/* Returns whether the query for 0x5BC yields a nonzero result. */
s32 is_script_flag_5bc_set(void) {
    return get_script_flag_mask(F_sbs11_pad25) != 0;
}
