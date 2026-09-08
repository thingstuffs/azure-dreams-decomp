#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B6CCC_0 {
    s32 unk_00;
    s32 unk_04;
} S_800B6CCC_0;   /* arg2 in func_800B6CCC */

/* Initialize an entry with a mode-dependent value offset and a fixed data offset. */
void func_800B6CCC(s32 mode, s32 value_base, S_800B6CCC_0 *entry, s32 data_base) {
    s32 entry_value;

    entry_value = value_base + 0x42E6;
    if (mode == 0) {
        entry_value = value_base + 0x42DB;
    }
    entry->unk_04 = entry_value;
    entry->unk_00 = (s32) (data_base + 0x80800000);
}
