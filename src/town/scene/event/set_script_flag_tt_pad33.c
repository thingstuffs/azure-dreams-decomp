#include "town/player.h"
#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/event.h"

/* Calls set_script_flag_bit with ID 0xD52. */
void set_script_flag_tt_pad33(void) {
    set_script_flag_bit(Ftt_pad33);
}
