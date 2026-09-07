#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"



typedef struct S_80172E80_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80172E80_1;   /* flags_base in func_80172E80 */




#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80047784();
M2C_UNK func_8009C93C();
s32 func_800A0134();
s32 func_800A04F0();
s32 func_800A2B5C();
s32 func_800A2CB8();
M2C_UNK func_800C7930();

extern s16 D_80083228;
extern s32 D_80083460;
extern u16 D_80083462;
extern u8 D_800E2378;

s32 func_80172E80(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    s32 result;
    s32 state;
    s32 value;
    s32 flags;
    s32 *flags_base;
    u8 *table;

    ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 &= 0x7F;
    flags_base = &D_80083460;
    state = 0;
    if (((S_80172E80_1 *)flags_base)->unk_02 & 0x2000) {
        goto return_minus_one;
    }

    value = func_800A04F0(arg3, ((Rec_D_80082E80 *)arg2)->unk_24,
                         ((Rec_D_80082E80 *)arg2)->unk_25,
                         ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16);
    result = 0;
    if ((func_800A2CB8(arg3, value) << 16) == 0) {
        goto return_zero;
    }

    result = -1;
    flags = ((S_80172E80_1 *)flags_base)->unk_02;
    if (flags & 0x2000) {
        return result;
    }
    if (!(((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000)) {
        if (flags & 8) {
            return result;
        }
    }

    if ((u16)((0 - func_800A0134(value, arg3)) + 0x40) >= 0x81U) {
        return state;
    }

    state = 1;
    if (!(((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000)) {
        if (D_80083462 & 8) {
            return -1;
        }
    }
    if ((func_800A2B5C(arg3) << 16) != 0) {
        return -1;
    }

    func_800C7930((s8 *)arg3 - 0x20, arg1, 8, 0x300);
    if ((func_800A2B5C(arg3) << 16) != 0) {
return_minus_one:
        return -1;
    }

    result = state;
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_9B.as_u8 = 0;
    if (result != 0) {
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0x11;
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = 0;
        ((Rec_D_800E3D7C *)arg3)->unk_84.as_u8 = 0x7C;
        ((Rec_D_800E3D7C *)arg3)->unk_85.as_u8 = 0;
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 &= 0xFFFBFFFF;
        table = &D_800E2378;
        (*(u8 **)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
                      table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                      0);
        ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8--;
        func_8009C93C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1, 0);
    }
    return result;

return_zero:
    return 0;
}
