#include "common.h"

extern u8 D_80013614[16];

/* ORs 3 into the indexed two-bit field if the flag's low 16 bits are nonzero, otherwise 1. */
void setPacked2bitFlag(s32 field_index, s32 flag) {
    u8 *packed_byte;
    s32 byte_index;
    u16 bit_shift;
    u8 old_byte;
    s32 field_bits;

    /* Integer page: docs/evidence/r97_decisions.md, decision 44.
       Runtime-indexed base has two genuine uses: byte load and byte store.
       Retail uses page 0x80010000 plus access offset 0x3614. */
    packed_byte = (u8 *)0x80010000U;
    byte_index = (s16)field_index >> 2;
    packed_byte = packed_byte + byte_index;
    bit_shift = (field_index & 3) << 1;
    old_byte = packed_byte[0x3614];
    field_bits = 1;
    if ((flag << 16) != 0) {
        field_bits = 3;
    }
    packed_byte[0x3614] = old_byte | (field_bits << bit_shift);
}
