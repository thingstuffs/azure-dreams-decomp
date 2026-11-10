#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"


/* Returns whether the query for ID 0x9A is nonzero. */
s32 is_script_flag_9a_set(void) {
    return get_script_flag_mask(F_viv_engei_ok) != 0;
}
