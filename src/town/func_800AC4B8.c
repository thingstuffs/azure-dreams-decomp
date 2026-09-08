#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A9C18_0 {
    u8 pad_00[0x35C4];
    u8 unk_35C4;
} S_800A9C18_0;   /* temp_a0 in func_800A9C18 */

/* Increments the selected byte counter and clamps the result to three. */
void func_800A9C18(s32 entry_index) {
    u8 count;
    S_800A9C18_0 *entry;
    void *table_base;

    table_base = (void *) 0x80010000;
    entry = (entry_index * 4) + table_base;
    count = entry->unk_35C4 + 1;
    entry->unk_35C4 = count;
    if ((u32) (count & 0xFF) >= 4U) {
        entry->unk_35C4 = 3U;
    }
}
