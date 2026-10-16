#include "common.h"
#include "m2c_compat.h"

typedef struct S_800998A4_0 {
    union { u8 s; s8 u; } unk_00;   /* accessed as both */
} S_800998A4_0;   /* arg0 in dungeonWriteFullwidthPrefixBytes */


/* Writes bytes 0x81 and 0x21 and returns the next output position. */
void *dungeonWriteFullwidthPrefixBytes(void *out) {
    ((S_800998A4_0 *)out)->unk_00.s = 0x81;
    out += 1;
    ((S_800998A4_0 *)out)->unk_00.u = 0x21;
    return out + 1;
}
