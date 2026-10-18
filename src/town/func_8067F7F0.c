/* Relinked copy of town/func_804804BC (func_804804BC.c); retail differs only at relocation sites. */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"



extern s32 D_800188C8;

/* Decrements the current state's counter by D_800188C8. */
void decrement_state_counter(void) {
    TownStateRecord *counter_state;

    counter_state = D_80016000->unk_38;
    counter_state->unk_2D5C = (s32) (((signed int)counter_state->unk_2D5C) - D_800188C8);
}
