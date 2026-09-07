#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800374F4();
M2C_UNK func_8009196C();
M2C_UNK func_80094048();
M2C_UNK func_80094378();
M2C_UNK func_80094944();
M2C_UNK func_80094C1C();
M2C_UNK func_8009503C();
M2C_UNK func_800951B4();
s16 func_80095978();
M2C_UNK func_80095A94();
M2C_UNK func_80095C80();
M2C_UNK func_800A895C();
extern u8 D_80083160[];
extern u8 D_800CFCEF[];
extern u8 D_800D043C[];
extern u8 D_800FE488[];
extern s32 D_800FE4E0;

void func_800917EC(void *arg0, void *arg1, M2C_UNK arg2) {
    u8 *state = D_80083160;
    s16 temp_v0;
    s16 temp_v0_3;
    s32 *temp_s0;
    s32 state_flags;
    u16 temp_v0_2;

    func_80095C80(arg1);
    func_800951B4(arg1);
    temp_v0 = func_80095978(arg1, D_800FE488);
    if ((temp_v0 - M2C_FIELD(arg1, s16 *, 0xA)) >= 4) {
        if (D_800CFCEF[0] == 0) {
            func_80094378(arg0, arg1, arg2);
            func_8009196C();
            return;
        }
    } else if (D_800CFCEF[0] == 0) {
        func_80095A94(arg1, temp_v0, D_800FE488);
    }
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0xA) - 1;
    M2C_FIELD(arg0, u16 *, 0xA) = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, 0xA) = (u16)(func_800374F4(4) + 3);
        D_800FE4E0 = M2C_FIELD(arg1, s32 *, 0);
        temp_s0 = &D_800FE4E0;
        M2C_FIELD(temp_s0, s32 *, 4) = M2C_FIELD(arg1, s32 *, 4);
        M2C_FIELD(temp_s0, s32 *, 8) =
            M2C_FIELD(arg1, s32 *, 8) + 0xFFB00000;
        func_800A895C(temp_s0, D_800D043C,
                      (func_800374F4(2) & 0xFFFF) + 2);
    }
    state_flags = M2C_FIELD(state, s32 *, 8);
    if ((state_flags & 0xF000) && (state_flags & 0x20)) {
        temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x3E) - 1;
        M2C_FIELD(arg0, u16 *, 0x3E) = (u16)temp_v0_3;
        func_80094944(temp_v0_3, 8);
        func_80094C1C(arg0);
        func_8009503C(arg1);
        func_8009196C();
        return;
    }
    func_80094048(arg0, arg1, arg2);
}
