#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"

void dungeonDrawFillerFirstNumber(); /* extern */

typedef struct S_800DC000_0 {
    u8 pad_00[0xFC];
    s32 unk_FC;
} S_800DC000_0;   /* *state in dungeonHandleCachedStateChange */

typedef struct S_800DC000_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800DC000_1;   /* arg0 in dungeonHandleCachedStateChange */

/* Handle changes to the state value and update its cached copy. */
void dungeonHandleCachedStateChange(S_800DC000_1 *cache) {
    void **state = (void **)(&D_800814A8);

    if (((S_800DC000_0 *)(*state))->unk_FC != cache->unk_04) {
        dungeonDrawFillerFirstNumber(((S_800DC000_0 *)(*state))->unk_FC, cache->unk_04, 8, 0x1A8, 0x1E0, 0);
        cache->unk_04 = ((S_800DC000_0 *)(*state))->unk_FC;
    }
}
