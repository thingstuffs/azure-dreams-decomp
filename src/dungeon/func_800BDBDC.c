#include "common.h"

typedef s32 M2C_UNK;

typedef struct {
    u8 pad_0[0xA];
    u16 field_A;
} D_80083460_Type;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8008D330();
M2C_UNK func_80098B38();
M2C_UNK func_80099844();
s32 func_800A2424();
M2C_UNK func_800A5F38();
M2C_UNK func_800A63B8();
s32 func_800AD6FC();
s32 func_800C3428();
extern M2C_UNK D_80082E80;
extern D_80083460_Type D_80083460;
extern M2C_UNK D_80083780;
extern u16 D_800DDE84[];
extern M2C_UNK D_800E173A;
extern s32 D_800E3D7C;


typedef struct S_800C333C_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0xFC];
    s32 unk_110;
} S_800C333C_0;   /* arg0 in func_800C333C */

s32 func_800C333C(S_800C333C_0 *arg0, s32 arg1, s16 arg2) {
    if (arg0 == D_800E3D7C) {
        arg0->unk_110 = arg1;
        func_8008D330(arg0, &D_80083780, &D_80082E80, arg0);
        func_800C3428();
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(
                arg0,
                (D_800DDE84[arg0->unk_13] >> 6) & 3,
                0) == 0) {
            func_800A5F38(arg0, arg1);
            func_800C3428();
            return 1;
        }
    }
    if (func_800A2424(arg0, 1) == 0) {
        func_80099844(arg0, &D_800E173A);
    }
    func_80098B38(arg1);
    {
        D_80083460_Type *state = &D_80083460;
        state->field_A = (u16) (state->field_A - 1);
    }
    return 1;
}
