#include "script_symbols.h"
#include "common.h"
#include "town/data.h"
#include "town/player/state.h"

/* Advances a counter, wraps values above 20 to 9, and chooses the event handler for values 8 and 20. */
void advance_counter_and_dispatch_event(void)
{
    s16 temp;

    temp = town_event_counter + 1;
    town_event_counter = temp;
    if (temp >= 0x15) {
        town_event_counter = 9;
    }
    if ((town_event_counter == 8) || (town_event_counter == 0x14)) {
        set_script_flag_bit(F_sbs42_pad14);
        return;
    }
    clear_script_flag_bit(F_sbs42_pad14);
}
