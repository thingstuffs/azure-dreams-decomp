#include "common.h"

extern s32 D_800834B8;
extern void func_800A553C(void *record_data, s32 unused_1, s32 unused_2);

/* Update the target using two values from the preceding state block. */
void func_800A5598(void) {
    s32 *target = &D_800834B8;
    s32 *source_state = target - 8;


    func_800A553C(target, source_state[2], source_state[3]);
}
