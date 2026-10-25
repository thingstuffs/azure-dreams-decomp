#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"
#include "town/player.h"


/* Runs set_script_flag_bit with code 0x1452 and its set_referenced_object_active_flag follow-up. */
void process_event_1452_and_refresh(void) {
    set_script_flag_bit(F_s04_niko_step);
    set_referenced_object_active_flag();
}
