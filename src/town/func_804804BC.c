#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern s32 D_80019438;

/* Decrements the current state's counter by D_80019438. */
void func_804804BC(void) {
    TownStateRecord *counter_state;

    counter_state = D_80016000->unk_38;
    counter_state->unk_2D5C = (s32) (((signed int)counter_state->unk_2D5C) - D_80019438);
}
