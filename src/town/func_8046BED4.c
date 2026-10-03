#include "shared/town_event_state.h"
#include "common.h"
#include "m2c_compat.h"


extern M2C_UNK D_8001FB20;

/* Increment the record's byte counter and return D_8001FB20. */
M2C_UNK *func_8001CED4(void) {
    D_8001E950->dispatchState = (u8) (D_8001E950->dispatchState + 1);
    return &D_8001FB20;
}
