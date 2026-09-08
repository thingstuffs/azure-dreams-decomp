#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_800ADB30_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x18];
    s32 unk_20;
} S_800ADB30_0;   /* arg0 in func_800ADB30 */

/* Pass the indexed four-byte entry address to func_800494B4. */
void func_800ADB30(S_800ADB30_0 *entry_table) {
    func_800494B4(entry_table->unk_20 + (entry_table->unk_04 * 4));
}
