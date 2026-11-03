#include "shared/town_event_state.h"
#include "common.h"
#include "town/scene/event.h"

typedef void (*TownCallback)(void);




/* Invoke one of two callbacks using the current state index. */
void invoke_event_state_callback(void)
{
    TownCallback callbacks[2] = {
        (TownCallback)advance_event_state_and_get_resource,
        (TownCallback)reset_event_entry_and_get_resource,
    };

    callbacks[town_event_state->dispatchState]();
}

/* MECHANISM: A two-entry sibling stack array creates the retail 0x20 frame and 0x10/0x14 callback
   slots; the callback's void ABI emits no args. */
