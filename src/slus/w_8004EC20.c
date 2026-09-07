#include "common.h"

/* Guarded dispatch: if both flag bytes are set, spin (polling func_8004EBDC via
 * func_80044618(2)) until func_8004EBDC() returns nonzero, then invoke the
 * callback selected from D_80071654[idx] with (this-0x20) as its argument and
 * return its result; otherwise return 0. */
typedef struct S_8004EC20 {
    u8 pad00[4];
    s32 idx;       /* 0x4: index into D_80071654 callback table */
    u8 b8;         /* 0x8 */
    u8 b9;         /* 0x9 */
} S_8004EC20;

extern s32 func_8004EBDC(void);
extern void func_80044618(s32);

extern s32 (*D_80071654[])(void *);

s32 func_8004EC20(S_8004EC20 *s0) {
    s32 ret = 0;

    if (s0->b8 != 0) {
        if (s0->b9 != 0) {
            while (func_8004EBDC() == 0) {
                func_80044618(2);
            }
            ret = D_80071654[s0->idx]((void *)((u8 *)s0 - 0x20));
        }
    }
    return ret;
}
