#include "common.h"

extern s32 D_800834B8;
extern void func_800A553C(void *arg0, s32 arg1, s32 arg2);

/* Update the target using two values from the preceding state block. */
void func_800A5598(void) {
    s32 *target = &D_800834B8;
    s32 *source_state = target - 8;

    
    func_800A553C(target, source_state[2], source_state[3]);
}
