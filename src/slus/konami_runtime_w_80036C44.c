#include "common.h"

#include "common.h"

typedef struct Func37534State Func37534State;
s32 func_80037534(Func37534State *state);                                /* extern */
void func_800478B8(void *entity);                     /* extern */

/* Forwards the value to func_800478B8 when func_80037534 returns zero. */
void func_80036C44(s32 unused_0, s32 unused_1, s32 value) {
    if (func_80037534((Func37534State *)unused_0) == 0) {
        func_800478B8(value);
    }
}
