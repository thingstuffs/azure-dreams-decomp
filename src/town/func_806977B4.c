#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern s32 D_80018AE0;

/* Add D_80018AE0 to the current state's accumulator. */
void func_806977B4(void) {
    TownStateRecord *state;

    state = D_80016000->unk_38;
    state->unk_2D5C = (s32) (((signed int)state->unk_2D5C) + D_80018AE0);
}
