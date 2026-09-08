#include "common.h"

extern s32 D_801749BC[];
extern s32 *D_80174704;
extern s32 D_80174CCC;
extern s16 D_80174CD0;

/* Select a table entry, reset its counter, and mark the object state active. */
void func_8016DF10(s32 table_index) {
    s8 *state;

    D_80174CD0 = 0;
    state = (s8 *)D_80174704 + 0x20;
    D_80174CCC = D_801749BC[table_index];
    state[0xB2] = 1;
    *(s16 *)(state + 0xAC) = table_index;
}
