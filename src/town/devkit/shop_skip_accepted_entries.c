#include "common.h"
#include "m2c_compat.h"

typedef struct ListLink {
    u16 first;
    u16 next;
} ListLink;

s32 shop_test_indexed_flag();                             /* extern */
extern ListLink D_80701DFC[];
extern s16 *D_80701DEC[];

/* Skips entries accepted by shop_test_indexed_flag and checks whether the next entry is zero. */
s32 shop_skip_accepted_entries(s32 list_index) {
    s16 *entry;

    entry = D_80701DEC[D_80701DFC[list_index].next];
    while (shop_test_indexed_flag(*entry) != 0) {
        entry += 1;
    }
    return *entry == 0;
}
