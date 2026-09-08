#include "common.h"
#include "m2c_compat.h"

typedef struct S_800DCA1C_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800DCA1C_0;   /* ((*var_a1 * 0x10) + arg0) in func_800DCA1C */

extern u8 D_800E2954;
extern u8 D_800E2960[];

/* Link entries to their predecessors in the selected index order and return the last entry. */
s32 func_800DCA1C(s32 entries_base, s32 use_alt_order) {
    s32 prev_entry;
    u8 *index_ptr;
    u8 *index_order;
    u8 entry_index;

    prev_entry = 0;
    if (use_alt_order != 0) {
        index_order = D_800E2960;
    } else {
        index_order = &D_800E2954;
    }
    if (*index_order < 9U) {
        index_ptr = index_order;
        do {
            ((S_800DCA1C_0 *)(((*index_ptr * 0x10) + entries_base)))->unk_0C = prev_entry;
            entry_index = *index_ptr;
            index_ptr += 1;
            prev_entry = entries_base + (entry_index * 0x10);
        } while ((u8) *index_ptr < 9U);
    }
    return prev_entry;
}
