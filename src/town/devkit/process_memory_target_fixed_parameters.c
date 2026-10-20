#include "common.h"

extern void func_804086CC(void);
extern void func_804086BC(s32, s32, s32);

/* Prepare state and process the target with fixed parameters 63 and 0. */
void process_memory_target_fixed_parameters(s32 target) {
    s32 saved_target = target;

    func_804086CC();
    func_804086BC(saved_target, 63, 0);
}
