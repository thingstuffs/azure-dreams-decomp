#include "common.h"

/* Look up a byte field (offset 0x10) in a 20-byte-per-entry table indexed by
 * a signed 16-bit id, then test a 2-bit hash of (val ^ (val>>4)) for zero. */

typedef struct {
    u8 unk00[0x10];
    u8 unk10;
    u8 unk11[3];
} S_8006DE24_Entry;

extern S_8006DE24_Entry D_8006DE24[];

s32 func_800439BC(s16 arg0) {
    u32 v = D_8006DE24[arg0].unk10;
    return ((v ^ (v >> 4)) & 3) == 0;
}
