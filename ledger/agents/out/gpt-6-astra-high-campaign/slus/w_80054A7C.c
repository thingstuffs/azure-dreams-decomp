#include "common.h"

extern void func_800540A8(void);
extern void func_800541E8(void);
extern void func_80055B44(s32 a0);

/* Dispatches an audio action by its low byte, preserving the low 16 bits for volume updates. */
void func_80054A7C(s32 action) {
    register s32 action_value ASM_REG("$3") = action;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    action = action & 0xFF;
    if (action == 3) {
        goto case3;
    }
    if (action < 4) {
        goto rangelow;
    }
    if (action == 4) {
        goto case4;
    }
    goto end;
rangelow:
    if (action == 0) {
        goto end;
    }
    func_80055B44(action_value & 0xFFFF);
    goto end;
case3:
    func_800540A8();
    goto end;
case4:
    func_800541E8();
end:
    return;
}
