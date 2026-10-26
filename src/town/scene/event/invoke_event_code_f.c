#include "town/player.h"
#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

/* Calls set_script_flag_bit with the constant 0x145F. */
void invoke_event_code_145_f(void) {
    set_script_flag_bit(Ftt_fkoya_isaku_scene00_ok);
}
