/* Relinked copy of town/func_80878110 (func_80878110.c); retail differs only at relocation sites. */
#include "common.h"
#include "town/scene.h"

typedef struct ListLink {
    u16 first;
    u16 next;
} ListLink;

s32 func_80000BE4(s32 flag_index);                             /* extern */
extern ListLink D_00000DB4[];
extern s16 *D_00000DB0[];

/* Skips entries accepted by func_80000BE4 and checks whether the next entry is zero. */
s32 is_next_entry_zero_after_skipping_b(s32 list_index) {
    s16 *entry;

    entry = D_00000DB0[D_00000DB4[list_index].next];
    while (func_80000BE4(*entry) != 0) {
        entry += 1;
    }
    return *entry == 0;
}
