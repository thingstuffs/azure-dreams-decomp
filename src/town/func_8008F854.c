#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_8008CFB4_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8008CFB4_0;   /* arg0 in townForwardSmallestSurfaceXQuery */

/* Pass three signed record components to townFindSmallestSurfaceXAcrossTiles. */
s16 townForwardSmallestSurfaceXQuery(S_8008CFB4_0 *record) {
    return townFindSmallestSurfaceXAcrossTiles(record->unk_02, record->unk_06, record->unk_0A);
}
