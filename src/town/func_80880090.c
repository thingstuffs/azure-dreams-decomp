/* Relinked copy of town/func_80878670 (func_80878670.c); retail differs only at relocation sites. */
#include "common.h"

extern s32 *D_807013A0[];

/* Set the indexed flag bit unless the index is zero. */
void func_80701090(s32 bit_index) {
    if (bit_index != 0) {
        D_807013A0[0][bit_index / 32] |= (1 << (bit_index % 32));
    }
}
