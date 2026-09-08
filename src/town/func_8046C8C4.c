#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_8001E578();                 /* extern */

typedef struct S_8046C8C4_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8046C8C4_0;   /* arg0 in func_8046C8C4 */

typedef struct S_8046C8C4_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_8046C8C4_1;   /* temp_a1 in func_8046C8C4 */

/* Pass the indexed entry and its identifier to the handler. */
void func_8046C8C4(S_8046C8C4_0 *table, s32 entry_index) {
    S_8046C8C4_1 *entry;

    entry = (entry_index * 0x10) + table->unk_10;
    func_8001E578(entry->unk_0C, entry);
}
