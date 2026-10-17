#include "common.h"
#include "m2c_compat.h"

void townSetScriptFlagBit();                 /* extern */

typedef struct S_80019958_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80019958_0;   /* arg0 in townSetIndexedEntryFlag */

typedef struct S_80019958_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80019958_1;

/* Set the indexed entry flag using its identifier and entry pointer. */
void townSetIndexedEntryFlag(S_80019958_0 *record, s32 entry_index) {
    townSetScriptFlagBit(((S_80019958_1 *)(record->unk_10 + entry_index * 0x10))->unk_0C);
}
