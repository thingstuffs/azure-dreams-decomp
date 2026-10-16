/* Relinked copy of town/func_808786C0 (func_808786C0.c); retail differs only at relocation sites. */
#include "common.h"

extern s32 *D_00000E54[];

/* Clear the indexed flag bit unless the index is one. */
void func_80000B90(s32 bit_index) {
    if (bit_index != 1) {
        D_00000E54[0][bit_index / 32] &= ~(1 << (bit_index % 32));
    }
}
