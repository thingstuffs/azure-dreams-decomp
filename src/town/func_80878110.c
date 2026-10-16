#include "common.h"
#include "m2c_compat.h"

typedef struct ListLink {
    u16 first;
    u16 next;
} ListLink;

s32 townShopTestIndexedFlag();                             /* extern */
extern ListLink D_80701DFC[];
extern s16 *D_80701DEC[];

/* Skips entries accepted by townShopTestIndexedFlag and checks whether the next entry is zero. */
s32 townShopSkipAcceptedEntries(s32 list_index) {
    s16 *entry;

    entry = D_80701DEC[D_80701DFC[list_index].next];
    while (townShopTestIndexedFlag(*entry) != 0) {
        entry += 1;
    }
    return *entry == 0;
}
