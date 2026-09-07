#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_800A55CC_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_800A55CC_0_pre;   /* the 0x10 bytes before arg0 in func_800A55CC, addressed as arg0[-1] */

typedef struct S_800A55CC_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A55CC_1;   /* arg1 in func_800A55CC */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033CD8();
M2C_UNK func_800942B0();
extern M2C_UNK D_800903FC[];
extern M2C_UNK D_800970FC[];
extern s32 D_800D0CC0[];

void func_800A55CC(void *arg0, S_800A55CC_1 *arg1) {
    s32 delta;

    ((S_800A55CC_0_pre *)arg0)[-1].unk_00 = D_800903FC;
    func_800942B0();
    {
        register void *call_arg0 ASM_REG("$4") = arg0;   /* MATCH pin: retail schedule: same instructions, different order without it */
        void *call_arg1 = D_800970FC;

        ASM_KEEP(call_arg0);   /* MATCH pin: keeps a statement from moving across a call/branch */
        delta = 0x10000;
        arg1->unk_08 =
            (arg1->unk_08 + delta) - D_800D0CC0[0];
        func_80033CD8(call_arg0, call_arg1, delta);
    }
}
