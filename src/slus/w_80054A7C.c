#include "common.h"

extern void func_800540A8(void);
extern void func_800541E8(void);
extern void func_80055B44(s32 a0);

/* Dispatches an audio action by its low byte, preserving the low 16 bits for volume updates. */
void func_80054A7C(s32 action) {
    u16 action_value = action;
    action = action & 0xFF;
    if (action != 3) {
        if (action >= 4) {
            if (action == 4) {
                goto case4;
            }
            return;
        }
        if (action == 0) {
            return;
        }
        func_80055B44(action_value & 0xFFFF);
        return;
    }
    func_800540A8();
    return;
case4:
    func_800541E8();
    return;
}
