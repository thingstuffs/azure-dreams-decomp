/* Relinked copy of town/func_80878110 (func_80878110.c); retail differs only at relocation sites. */
#include "common.h"

typedef struct ListLink {
    u16 first;
    u16 next;
} ListLink;

s32 test_indexed_flag_treating_indices();                             /* extern */
extern ListLink D_00003F88[];
extern s16 *D_00003F78[];

/* Skips entries accepted by test_indexed_flag_treating_indices and checks whether the next entry is zero. */
s32 skip_entries_accepted_next_entry(s32 list_index) {
    s16 *entry;

    entry = D_00003F78[D_00003F88[list_index].next];
    while (test_indexed_flag_treating_indices(*entry) != 0) {
        entry += 1;
    }
    return *entry == 0;
}
