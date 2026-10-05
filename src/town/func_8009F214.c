#include "common.h"

extern void func_8008F104(void *record, s32 setup_value, void *setup_param);
extern void func_8009B218(void *object, s32 context, void *state, void *init_value);

extern s32 D_800CFD00[];
extern s32 D_800F8CEC[];

// Assigns the state's data table and invokes the shared handlers.
void func_8009C974(void *context, s32 selector, void *state) {
    *(void **)((u8 *)state + 8) = D_800F8CEC;
    func_8008F104(context, selector, D_800CFD00);
    func_8009B218(context, selector, state, 0);
}
