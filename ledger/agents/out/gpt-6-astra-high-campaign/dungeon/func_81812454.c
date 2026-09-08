#include "common.h"

extern void func_80027328();
extern void func_80027384();
extern void func_800273E4();

/* Dispatch an update according to the mode and current state. */
void func_80027454(s32 *state, s32 mode, s32 value, s32 extra_value)
{
    if (mode == 0) {
        func_80027328(state, value);
        return;
    }
    if (*state != 0x13) {
        func_80027384(state, value);
        return;
    }
    func_800273E4(state, value, extra_value);
}
