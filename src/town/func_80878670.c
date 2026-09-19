#include "common.h"

extern s32 *D_807030A4[];

/* Set the indexed flag bit unless the index is zero. */
void func_80702670(s32 bit_index) {
    if (bit_index != 0) {
        D_807030A4[0][bit_index / 32] |= (1 << (bit_index % 32));
    }
}
