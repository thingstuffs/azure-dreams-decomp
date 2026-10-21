#include "shared/town_event_state.h"
#include "common.h"

extern void reset_dispatch_state_and_flags(void);

/* Call reset_dispatch_state_and_flags, increment the byte at D_8001E950, and return zero. */
s32 call_reset_dispatch_state_flags(s32 first_value, s32 second_value) {
    reset_dispatch_state_and_flags();
    town_event_state->unk_00 += 1;
    return 0;
}
