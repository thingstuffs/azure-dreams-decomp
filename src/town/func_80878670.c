#include "common.h"

extern s32 *D_807030A4[];

/* Set the indexed flag bit unless the index is zero. */
void func_80702670(s32 bit_index) {
    s32 index_or_word = bit_index;
    s32 bit_position;
    register s32 word_address ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 base_or_mask;

    if (index_or_word != 0) {
        bit_position = index_or_word;
        if (index_or_word < 0) {
            bit_position = index_or_word + 31;
        }
        bit_position >>= 5;
        word_address = bit_position << 2;
        bit_position <<= 5;
        word_address += (base_or_mask = (s32)D_807030A4[0],
                    bit_position = index_or_word - bit_position, base_or_mask);
        base_or_mask = 1;
        index_or_word = *(s32 *)word_address;
        base_or_mask <<= bit_position;
        base_or_mask |= index_or_word;
        *(s32 *)word_address = base_or_mask;
    }
}

/* MECHANISM: Frameless leaf with guarded roles a1=input/load, v1=quotient/remainder,
   a0=word offset/pointer, and v0=base/mask/result. The comma sequence exposes
   lw-global; subu; addu, filling the load delay and preserving retail order. */
