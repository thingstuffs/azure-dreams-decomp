/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"

extern void townConfigureTheSetModeN3(void *record, s32 setup_value, void *setup_param);
extern void townInitializeOptionalObjectState(void *object, s32 context, void *state, void *init_value);

extern s32 D_800D0648[];
extern s32 D_800F8D64[];

void func_8009CA24(void *context, s32 selector, void *state) {
    *(void **)((u8 *)state + 8) = D_800F8D64;
    townConfigureTheSetModeN3(context, selector, D_800D0648);
    townInitializeOptionalObjectState(context, selector, state, 0);
}
