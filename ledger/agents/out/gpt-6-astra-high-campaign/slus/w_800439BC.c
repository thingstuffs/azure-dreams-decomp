#include "common.h"

/* Look up a byte field (offset 0x10) in a 20-byte-per-entry table indexed by
 * a signed 16-bit id, then test a 2-bit hash of (val ^ (val>>4)) for zero. */

typedef struct {
    u8 unk00[0x10];
    u8 unk10;
    u8 unk11[3];
} S_8006DE24_Entry;

extern S_8006DE24_Entry D_8006DE24[];

/* Test whether the table byte XOR its upper nibble has its lowest two bits clear. */
s32 func_800439BC(s16 entry_id) {
    u32 value = D_8006DE24[entry_id].unk10;
    return ((value ^ (value >> 4)) & 3) == 0;
}
