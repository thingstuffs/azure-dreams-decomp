#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_80172274_0 {
    u16 unk_00;
    u8 pad_02[0x16];
    u16 unk_18;
} S_80172274_0;   /* arg0 in dungeonUpdateCascadingTrailEmitter; pointer addresses record offset 0x2 */


void dungeonSpawnRisingTrailEmitter();                            /* extern */

/* Decrement the record counter, calling the update on even counts and setting flags at zero. */
void dungeonUpdateCascadingTrailEmitter(void *record_data) {
    u16 remaining;

    if (!(((S_80172274_0 *)((u8 *)record_data - 0x2))->unk_18 & 1)) {
        dungeonSpawnRisingTrailEmitter();
    }
    remaining = ((S_80172274_0 *)((u8 *)record_data - 0x2))->unk_18 - 1;
    ((S_80172274_0 *)((u8 *)record_data - 0x2))->unk_18 = remaining;
    if ((remaining << 0x10) <= 0) {
        ((S_80172274_0 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_80172274_0 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        objectFlagBlock.flags = (s32) (objectFlagBlock.flags | 0x8000);
    }
}
