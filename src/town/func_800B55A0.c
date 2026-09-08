#include "common.h"
#include "m2c_compat.h"

s32 func_80049790();                             /* extern */

typedef struct S_800B2D00_0 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_800B2D00_0;   /* arg1 in func_800B2D00 */

/* Convert up to ten entries from the selected page into the output slots. */
void func_800B2D00(s32 **outputs, S_800B2D00_0 *page_info, s32 entries_base) {
    s32 **output_slot;
    s32 *entry_ptr;
    s32 entry;
    s32 page;
    s32 entry_index;
    s32 count;

    count = 0;
    page = page_info->unk_00;
    output_slot = outputs;
    entry_index = page * 0xA;
    entry_ptr = (page * 0x28) + entries_base;
next_entry:
    count += 1;
    if (entry_index < page_info->unk_0C) {
        entry = *entry_ptr;
        entry_ptr += 1;
        entry_index += 1;
        **output_slot = func_80049790(entry);
        output_slot += 1;
        if (count < 0xA) {
            goto next_entry;
        }
    }
}
