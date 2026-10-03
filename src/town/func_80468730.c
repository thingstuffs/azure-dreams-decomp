#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"



/* Increment the record counter if it is below two. */
void func_80019730(void) {
    u8 counter;

    counter = D_8001E950->dispatchState;
    if (counter < 2U) {
        D_8001E950->dispatchState = (u8) (counter + 1);
    }
}
