#include "common.h"
#include "m2c_compat.h"

s32 func_8002553C();                             /* extern */
void dungeonClearObjectBufferAndState();                         /* extern */

typedef struct S_800255D0_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800255D0_0;   /* arg0 in dungeonProcessResolvedItemValue */

/* Processes the value resolved from the record and returns success. */
s32 dungeonProcessResolvedItemValue(S_800255D0_0 *record) {
    dungeonClearObjectBufferAndState(func_8002553C(record->unk_14));
    return 1;
}
