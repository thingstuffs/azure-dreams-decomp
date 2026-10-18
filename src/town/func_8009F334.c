/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"

extern void configure_the_set_mode_n_3(void *record, s32 setup_value, void *setup_param);
extern void initialize_optional_object_state(void *object, s32 context, void *state, void *init_value);

extern s32 D_800D0648[];
extern s32 D_800F8D70[];

void func_8009CA94(void *context, s32 selector, void *state) {
    *(void **)((u8 *)state + 8) = D_800F8D70;
    configure_the_set_mode_n_3(context, selector, D_800D0648);
    initialize_optional_object_state(context, selector, state, 0);
}
