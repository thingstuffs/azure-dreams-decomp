/* Relinked copy of town/func_80878110 (func_80878110.c); retail differs only at relocation sites. */
#include "common.h"

typedef struct ListLink {
    u16 first;
    u16 next;
} ListLink;

s32 func_80003C70();                             /* extern */
extern ListLink D_00003F88[];
extern s16 *D_00003F78[];

/* Skips entries accepted by func_80003C70 and checks whether the next entry is zero. */
s32 func_80003668(s32 list_index) {
    s16 *entry;

    entry = D_00003F78[D_00003F88[list_index].next];
    while (func_80003C70(*entry) != 0) {
        entry += 1;
    }
    return *entry == 0;
}
