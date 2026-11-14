#include "town/player.h"
#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/event.h"

/* Invokes set_script_flag_bit with code 0xDAF. */
void set_script_flag_tt_pad127(void) {
    set_script_flag_bit(Ftt_pad127);
}
