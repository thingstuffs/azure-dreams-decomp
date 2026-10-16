#include "shared/town_event_state.h"
#include "common.h"

extern u8 D_8001FD7A[];

/* Reset byte 5 and set byte 1 of the first entry, then return D_8001FD7A. */
u8 *townResetEventEntryAndGetResource(void) {
    D_8001E950->unk_05 = 0;
    D_8001E950->dispatchState = 2;
    return D_8001FD7A;
}
