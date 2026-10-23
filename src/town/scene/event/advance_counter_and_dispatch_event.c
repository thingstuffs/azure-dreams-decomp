#include "script_symbols.h"
#include "common.h"

extern s16 town_event_counter;

extern void func_80017380(s32);
extern void func_800173F8(s32);

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
        func_80017380(F_sbs42_pad14);
        return;
    }
    func_800173F8(F_sbs42_pad14);
}
