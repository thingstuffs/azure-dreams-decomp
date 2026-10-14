#include "common.h"
#include "m2c_compat.h"

typedef struct ListLink {
    u16 first;
    u16 next;
} ListLink;

s32 func_80702714();                             /* extern */
extern ListLink D_80701DFC[];
extern s16 *D_80701DEC[];

/* Skips entries accepted by func_80702714 and checks whether the next entry is zero. */
s32 func_80702110(s32 list_index) {
    s16 *entry;

    entry = D_80701DEC[D_80701DFC[list_index].next];
    while (func_80702714(*entry) != 0) {
        entry += 1;
    }
    return *entry == 0;
}
