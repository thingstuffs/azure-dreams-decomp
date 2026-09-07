#include "common.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800352FC(void);
extern M2C_UNK func_800C337C();
extern M2C_UNK func_800C3A50();
extern M2C_UNK func_800C3A7C();
extern u8 D_80082660[9];
extern M2C_UNK D_800CFCB4[5];
extern volatile M2C_UNK D_800D5084[20];

void func_800C3988(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_v0;
    u8 temp_v1;
    u8 *entry;

    if (func_800352FC() == 0) {
        s32 *state;

        func_800C337C(arg0, arg1, arg2);
        state = D_800CFCB4;
        if (arg0 == state[4]) {
            state[4] = 0;
            func_800C3A7C();
        }
    } else {
        temp_v0 = M2C_FIELD(arg0, s32 *, 0x60) * 8;
        entry = &D_80082660[temp_v0];
        temp_v1 = *entry;
        if ((u32) (temp_v1 - 2) < 0x14U) {
            register void *call_arg0 ASM_REG("$4") = arg0;

            (void) D_800D5084[(s8) temp_v1];
            func_800C3A50(call_arg0, arg1);
            return;
        }
        if ((s8) temp_v1 >= 0x16) {
            M2C_FIELD((((s8) temp_v1 * 4) + M2C_FIELD(arg0, s32 *, 0x5C)), M2C_UNK (**)(void *, M2C_UNK, M2C_UNK), -0x58)(arg0, arg1, arg2);
            func_800C3A7C();
            return;
        }
        if ((s8) temp_v1 < 0) {
            *entry = 0U;
            func_800C337C(arg0, arg1, arg2);
        }
    }
}
