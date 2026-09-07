#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_800C3988_0_pre {
    M2C_UNK (*unk_00)(void *, M2C_UNK, M2C_UNK);
    u8 pad_04[0x54];
} S_800C3988_0_pre;   /* the 0x58 bytes before (((s8) temp_v1 * 4) + arg0->unk_5C) in func_800C3988, addressed as (((s8) temp_v1 * 4) + arg0->unk_5C)[-1] */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800352FC(void);
extern M2C_UNK func_800C337C();
extern M2C_UNK func_800C3A50();
extern M2C_UNK func_800C3A7C();
extern u8 D_80082660[9];
extern M2C_UNK D_800CFCB4[5];
extern volatile M2C_UNK D_800D5084[20];

typedef struct S_800C3988_0 {
    u8 pad_00[0x5C];
    s32 unk_5C;
    s32 unk_60;
} S_800C3988_0;   /* arg0 in func_800C3988 */

void func_800C3988(S_800C3988_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_v0;
    u8 temp_v1;
    u8 *entry;

    if (func_800352FC() == 0) {
        s32 *state;

        func_800C337C(arg0, arg1, arg2);
        state = D_800CFCB4;
        if (arg0 == state[4]) {
            state[4] = 0;
            return;
        }
    } else {
        temp_v0 = arg0->unk_60 * 8;
        entry = &D_80082660[temp_v0];
        temp_v1 = *entry;
        if ((u32) (temp_v1 - 2) < 0x14U) {
            register void *call_arg0 ASM_REG("$4") = arg0;   /* MATCH pin: retail schedule: same instructions, different order without it */

            (void) D_800D5084[(s8) temp_v1];
            func_800C3A50(call_arg0, arg1);
            return;
        }
        if ((s8) temp_v1 >= 0x16) {
            ((S_800C3988_0_pre *)((((s8) temp_v1 * 4) + arg0->unk_5C)))[-1].unk_00(arg0, arg1, arg2);
            return;
        }
        if ((s8) temp_v1 < 0) {
            *entry = 0U;
            func_800C337C(arg0, arg1, arg2);
        }
    }
}
