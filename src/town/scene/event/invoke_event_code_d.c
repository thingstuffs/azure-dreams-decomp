#include "town/player.h"
#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"
#include "town/scene/event.h"

/* Calls set_script_flag_bit with value 0xD76. */
void invoke_event_code_d_76(void) {
    set_script_flag_bit(Ftt_pad69);
}
