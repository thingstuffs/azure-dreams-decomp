#include "common.h"

/* Resolves a1 to an id via func_8002137C, then linear-searches the array at
 * a0->unk10[0..a0->unk24) for that id. Returns the matching index, or the
 * count (0 if the count is <= 0) when not found. Struct layout matches the
 * S_8004FDE0_sub inference in src/w_8004FDE0.c (unk10[0x14]=5 s32 slots,
 * unk24=live count). */
typedef struct S_8004FD78 {
    u8 pad00[0x10];   /* 0x00 */
    s32 unk10[5];     /* 0x10 - fixed-size id array (5 slots, per sibling struct) */
    s32 unk24;         /* 0x24 - live count */
} S_8004FD78;

extern s32 func_8002137C(void *a0);

s32 func_8004FD78(void *a0, void *a1)
{
    S_8004FD78 *s0 = (S_8004FD78 *)a0;
    s32 target = func_8002137C(a1);
    s32 count = s0->unk24;
    s32 i;

    for (i = 0; i < count; i++) {
        if (s0->unk10[i] == target) {
            return i;
        }
    }
    return i;
}
