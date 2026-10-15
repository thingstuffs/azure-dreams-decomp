/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"

extern void func_8008F104(void *record, s32 setup_value, void *setup_param);
extern void func_8009B218(void *object, s32 context, void *state, void *init_value);

extern s32 D_800D0648[];
extern s32 D_800F8D70[];

void func_8009CA94(void *context, s32 selector, void *state) {
    *(void **)((u8 *)state + 8) = D_800F8D70;
    func_8008F104(context, selector, D_800D0648);
    func_8009B218(context, selector, state, 0);
}
