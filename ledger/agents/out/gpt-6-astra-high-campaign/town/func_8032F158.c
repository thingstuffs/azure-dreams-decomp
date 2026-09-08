#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001ACE8();                 /* extern */

typedef struct S_80019958_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80019958_0;   /* arg0 in func_80019958 */

typedef struct S_80019958_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80019958_1;   /* temp_a1 in func_80019958 */

/* Set the indexed entry flag using its identifier and entry pointer. */
void func_80019958(S_80019958_0 *record, s32 entry_index) {
    S_80019958_1 *entry;

    entry = (entry_index * 0x10) + record->unk_10;
    func_8001ACE8(entry->unk_0C, entry);
}
