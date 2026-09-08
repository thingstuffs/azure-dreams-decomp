#include "common.h"
#include "records/Rec_func_8009EE9C_arg0.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800644B8();
M2C_UNK func_8009EF64();
M2C_UNK func_8009F1C0();
M2C_UNK func_8009F48C();
extern s32 D_800834B8[3];
extern M2C_UNK D_80093328;
extern M2C_UNK D_80093524[3];
extern s32 D_800CFCC4[3];


typedef struct S_8009EE9C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8009EE9C_0;   /* arg2 in func_8009EE9C */


void func_8009EE9C(Rec_func_8009EE9C_arg0 *arg0, s32 arg1, S_8009EE9C_0 *arg2, M2C_UNK arg3) {
    s32 temp_s0;

    temp_s0 = arg2->unk_08;
    arg2->unk_08 = (u32) (arg0->unk_A0 + (func_800644B8(arg0->unk_6C) << 6) + 0xFFFC0000);
    arg0->unk_6C = (s16) ((u16) arg0->unk_6C + 0x40);
    arg2->unk_14 = (s32) (arg2->unk_08 - temp_s0);
    if (D_800CFCC4[0] == arg1) {
        if (D_800834B8[0] == &D_80093328) {
            func_8009F1C0(arg0, D_800CFCC4[0], arg2, arg3);
            func_8009EF64();
            return;
        }
        if (D_800834B8[0] == D_80093524) {
            func_8009F48C(arg0, D_800CFCC4[0], arg2, arg3);
        }
    }
}
