#include "common.h"

extern u8 D_80013614[16];

/* ORs 3 into the indexed two-bit field if the flag's low 16 bits are nonzero, otherwise 1. */
void setPacked2bitFlag(s32 field_index, s32 flag) {
    u8 *packed_byte;
    s32 byte_index;
    s32 bit_shift;
    u8 old_byte;
    s32 field_bits;

    packed_byte = D_80013614;
    byte_index = (s16)field_index >> 2;
    packed_byte = packed_byte + byte_index;
    bit_shift = (field_index & 3) << 1;
    old_byte = *packed_byte;
    field_bits = 1;
    if ((flag << 16) != 0) {
        field_bits = 3;
    }
    *packed_byte = old_byte | (field_bits << bit_shift);
}
