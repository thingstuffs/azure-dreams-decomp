#include "script_symbols.h"
#include "shared/town_event_state.h"
#include "common.h"

extern void func_8001E578(s32);

/* Set three state bytes to 2 and dispatch event 0xA2. */
void set_event_state_and_dispatch_a_2(void) {
    town_event_state->unk_00 = 2;
    town_event_state->unk_05 = 2;
    town_event_state->dispatchState = 2;
    func_8001E578(F_end_ending);
}
