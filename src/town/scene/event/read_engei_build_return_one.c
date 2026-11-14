#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player.h"
#include "town/player/script_flags.h"


/* Calls get_script_flag_mask with ID 0x12C2 and returns 1. */
s32 read_engei_build_return_one(void) {
    get_script_flag_mask(F_engei_build);
    return 1;
}
