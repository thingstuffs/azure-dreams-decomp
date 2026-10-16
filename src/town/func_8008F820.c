#include "common.h"
#include "m2c_compat.h"

s16 townFindHighestSurfaceWithinRange();                   /* extern */

typedef struct S_8008CF80_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8008CF80_0;   /* arg0 in townForwardHighestSurfaceQuery */

/* Pass three signed record components to townFindHighestSurfaceWithinRange. */
s16 townForwardHighestSurfaceQuery(S_8008CF80_0 *record) {
    return townFindHighestSurfaceWithinRange(record->unk_02, record->unk_06, record->unk_0A);
}
