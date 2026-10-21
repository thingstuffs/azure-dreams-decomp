#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern s32 scene_charge;

/* Subtracts the global decrement from the current state's counter. */
void subtract_cached_value_from_money(void) {
    TownStateRecord *state;

    state = D_80016000->unk_38;
    state->unk_2D5C = (s32) (((signed int)state->unk_2D5C) - scene_charge);
}
