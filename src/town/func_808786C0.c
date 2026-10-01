#include "common.h"

extern s32 *D_807030A4[];

/* Clear the indexed flag bit unless the index is one. */
void func_807026C0(s32 bit_index) {
    if (bit_index != 1) {
        D_807030A4[0][bit_index / 32] &= ~(1 << (bit_index % 32));
    }
}
