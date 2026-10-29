/* Relinked copy of town/func_808786C0 (func_808786C0.c); retail differs only at relocation sites. */
#include "common.h"
#include "town/scene/flags.h"

extern s32 *D_A0700F44[];

/*
 * Clears the selected bit in D_A0700F44 using 32-bit word indexing, leaving reserved bit one
 * unchanged.
 */
void clear_indexed_flag_bit_unless_index_one(s32 bit_index) {
    if (bit_index != 1) {
        D_A0700F44[0][bit_index / 32] &= ~(1 << (bit_index % 32));
    }
}
