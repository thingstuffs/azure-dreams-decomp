#include "shared/town_event_state.h"
#include "common.h"

typedef void (*TownCallback)(void);

extern u8 D_8001CED4;
extern u8 D_8001CF1C;

/* Invoke one of two callbacks using the current state index. */
void invoke_event_state_callback(void)
{
    TownCallback callbacks[2] = {
        (TownCallback)&D_8001CED4,
        (TownCallback)&D_8001CF1C,
    };

    callbacks[town_event_state->dispatchState]();
}

/* MECHANISM: A two-entry sibling stack array creates the retail 0x20 frame and 0x10/0x14 callback
   slots; the callback's void ABI emits no args. */
