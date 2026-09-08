/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

s32 func_80049790();                             /* extern */

typedef struct S_800AF254_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800AF254_0;   /* *arg1 in func_800AF254 */

typedef struct S_800AF254_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    s32 unk_20;
} S_800AF254_1;   /* temp_v1 in func_800AF254 */

/* Fills up to ten output slots with converted entries from the selected page. */
void func_800AF254(s32 output_base, void **entries_ref) {
    s32 *output_slot;
    s32 entry_value;
    s32 entry_index;
    s32 slot_index;
    S_800AF254_1 *entries;

    slot_index = 0x1A;
    output_slot = output_base + 0x68;
    entry_index = ((S_800AF254_0 *)(*entries_ref))->unk_10 * 0xA;
next_entry:
    entries = *entries_ref;
    slot_index += 1;
    if (entry_index < entries->unk_1C) {
        entry_value = *(s32 *)((entry_index * 4) + entries->unk_20);
        entry_index += 1;
        *(*(s32 **)output_slot) = func_80049790(entry_value);
        output_slot += 1;
        if (slot_index < 0x24) {
            goto next_entry;
        }
    }
}
