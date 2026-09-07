#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((s8 *)(expr) + (offset)))

extern s32 func_80098464();
extern s32 func_80098480();
extern s32 func_80098488();
extern s32 func_80098490();
extern s32 func_80098988();
extern s16 func_800C2AE8();

void func_800983BC(void *arg0, void *arg1, s32 arg2) {
    s16 temp_a0;
    u16 temp_v0;
    register s32 side_v0 ASM_REG("$2");
    register s32 side_v1 ASM_REG("$3");

    FIELD(arg1, s16, 0xA) = func_800C2AE8(arg1);
    temp_v0 = FIELD(arg0, u16, 0xA) - 1;
    FIELD(arg0, u16, 0xA) = temp_v0;
    if ((s16)temp_v0 < 0) {
        func_80098988(arg0, arg1, arg2);
        func_80098490();
        return;
    }
    temp_a0 = FIELD(arg0, s16, 0x10);
    if (temp_a0 == 0x400) {
        goto case_400;
    }
    if (temp_a0 < 0x401) {
        if (temp_a0 == 0) {
            goto case_0;
        }
        func_80098480();
        return;
    }
    if (temp_a0 == 0xC00) {
        goto case_C00;
    }
    func_80098480();
    return;

case_400:
    side_v0 = FIELD(arg1, s32, 0);
    side_v1 = 0x120000;
    ASM_KEEP(side_v0);
    ASM_TAILSLOT_PIN(side_v1);
    func_80098464();
    return;

case_C00:
    FIELD(arg1, s32, 0) -= 0x120000;
    func_80098490();
    return;

case_0:
    side_v0 = FIELD(arg1, s32, 4);
    side_v1 = 0x120000;
    ASM_KEEP(side_v0);
    ASM_LIVE_SIBCALL_PIN(side_v1, 1179648);
    func_80098488();
    FIELD(arg1, s32, 4) -= 0x120000;
}
