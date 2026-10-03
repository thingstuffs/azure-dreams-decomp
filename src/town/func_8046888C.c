#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"



/* Returns whether the current record's unk_01 field is 2. */
s32 func_8001988C(void) {
    return D_8001E950->dispatchState == 2;
}
