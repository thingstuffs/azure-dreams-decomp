#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



/* Advance the two position components by their corresponding increments. */
void func_80614930(void) {
    TownPositionState *x_state;
    TownPositionState *y_state;

    x_state = D_80016000->unk_1C;
    x_state->x = (s32) (x_state->x + x_state->unk_10);
    y_state = D_80016000->unk_1C;
    y_state->y = (s32) (y_state->y + y_state->unk_14);
}
