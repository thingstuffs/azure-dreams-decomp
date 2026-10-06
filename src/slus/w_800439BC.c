#include "common.h"
#include "shared/def_table.h"

/* Look up a byte field (offset 0x10) in a 20-byte-per-entry table indexed by
 * a signed 16-bit id, then test a 2-bit hash of (val ^ (val>>4)) for zero. */


/* Test whether the table byte XOR its upper nibble has its lowest two bits clear. */
s32 func_800439BC(s16 entry_id) {
    u32 value = D_8006DE24[entry_id].unk_10;
    return ((value ^ (value >> 4)) & 3) == 0;
}
