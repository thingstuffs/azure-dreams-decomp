#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A2CAC_0 {
    u8 pad_00[0x25];
    u8 unk_25;
} S_800A2CAC_0;   /* arg0 in func_800A2CAC */

/* Checks whether the record's byte at offset 0x25 is below 0x40. */
s32 func_800A2CAC(S_800A2CAC_0 *record) {
    return (u8) record->unk_25 < 0x40U;
}
