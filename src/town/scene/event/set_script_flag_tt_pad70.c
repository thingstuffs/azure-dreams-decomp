#include "town/player.h"
#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/event.h"

/* Passes 0xD77 to set_script_flag_bit. */
void set_script_flag_tt_pad70(void) {
    set_script_flag_bit(Ftt_pad70);
}
