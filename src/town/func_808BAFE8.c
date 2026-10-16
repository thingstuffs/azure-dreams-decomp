/* Relinked copy of town/func_80878110 (func_80878110.c); retail differs only at relocation sites. */
#include "common.h"

typedef struct ListLink {
    u16 first;
    u16 next;
} ListLink;

s32 func_80000C6C();                             /* extern */
extern ListLink D_00000F28[];
extern s16 *D_00000F20[];

/* Skips entries accepted by func_80000C6C and checks whether the next entry is zero. */
s32 func_800007E8(s32 list_index) {
    s16 *entry;

    entry = D_00000F20[D_00000F28[list_index].next];
    while (func_80000C6C(*entry) != 0) {
        entry += 1;
    }
    return *entry == 0;
}
