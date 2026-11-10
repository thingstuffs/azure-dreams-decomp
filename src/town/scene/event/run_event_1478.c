#include "script_symbols.h"
#include "common.h"
#include "town/player/state.h"


/* Calls func_80018B58 with ID 0x1478. */
void run_event_1478(void) {
    set_script_flag_bit(Ft_cheriru_love);
}
