#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009B120_0 {
    u8 unk_00;
    u8 unk_01;
} S_8009B120_0;   /* arg0 in func_8009B120 */

/* Checks whether the record's first two bytes are 4 and 0xD. */
s32 func_8009B120(S_8009B120_0 *record) {
    s32 matches;

    matches = 0;
    if (record->unk_01 == 0xD) {
        matches = record->unk_00 == 4;
    }
    return matches;
}
