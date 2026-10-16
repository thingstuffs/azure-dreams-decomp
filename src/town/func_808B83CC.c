/* Relinked copy of town/func_80878670 (func_80878670.c); retail differs only at relocation sites. */
#include "common.h"

extern s32 *D_000045FC[];

/* Set the indexed flag bit unless the index is zero. */
void func_80003BCC(s32 bit_index) {
    if (bit_index != 0) {
        D_000045FC[0][bit_index / 32] |= (1 << (bit_index % 32));
    }
}
