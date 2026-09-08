#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800197D8();                 /* extern */

typedef struct S_8047C324_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8047C324_0;   /* arg0 in func_8047C324 */

typedef struct S_8047C324_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_8047C324_1;   /* temp_a1 in func_8047C324 */

/* Pass the indexed entry and its identifier to func_800197D8. */
void func_8047C324(S_8047C324_0 *entry_table, s32 entry_index) {
    S_8047C324_1 *entry;

    entry = (entry_index * 0x10) + entry_table->unk_10;
    func_800197D8(entry->unk_0C, entry);
}
