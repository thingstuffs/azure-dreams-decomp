/* Relinked copy of town/func_804713B8 (func_804713B8.c); retail differs only at relocation sites. */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"



extern s32 D_800188C8;

/* Adds the global increment to the current state's accumulator. */
void func_80016818(void) {
    TownStateRecord *state;

    state = D_80016000->unk_38;
    state->unk_2D5C = (s32) (((signed int)state->unk_2D5C) + D_800188C8);
}
