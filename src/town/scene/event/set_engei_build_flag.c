#include "town/player.h"
#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/event.h"

/* Calls set_script_flag_bit with argument 0x12C2. */
void set_engei_build_flag(void) {
    set_script_flag_bit(F_engei_build);
}
