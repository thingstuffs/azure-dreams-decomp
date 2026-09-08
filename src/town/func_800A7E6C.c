#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef s32 M2C_UNK;

typedef struct S_800A55CC_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_800A55CC_0_pre;   /* the 0x10 bytes before arg0 in func_800A55CC, addressed as arg0[-1] */



#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033CD8();
M2C_UNK func_800942B0();
extern M2C_UNK D_800903FC[];
extern M2C_UNK D_800970FC[];
extern s32 D_800D0CC0[];

void func_800A55CC(void *arg0, Rec_D_800E3D7C *arg1) {
    s32 delta;

    ((S_800A55CC_0_pre *)arg0)[-1].unk_00 = D_800903FC;
    func_800942B0();
    {
        register void *call_arg0 ASM_REG("$4") = arg0;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        void *call_arg1 = D_800970FC;

        ASM_KEEP(call_arg0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        delta = 0x10000;
        arg1->unk_08.at00_s32.v =
            (arg1->unk_08.at00_s32.v + delta) - D_800D0CC0[0];
        func_80033CD8(call_arg0, call_arg1, delta);
    }
}
