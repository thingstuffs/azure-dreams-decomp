#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80033CD8();
extern M2C_UNK func_80033D08();
extern s32 func_8009D20C();
extern M2C_UNK func_800A8BBC();
extern M2C_UNK func_800A96F0();
extern s32 D_800814A0;
extern M2C_UNK D_800A9528;

#define FIELD(base, type, offset) (*(type)((s8 *)(base) + (offset)))

void func_800A9624(void *arg0, s32 arg1, M2C_UNK arg2) {
    s32 state;
    M2C_UNK (*callback)(void *, s32, M2C_UNK);

    state = func_8009D20C();
    if (state == 1) {
        func_800A8BBC(0x1B, 0x1C, 0x1D, 0x1E, arg1);
        if (FIELD(arg0, s8 **, 0x98) != 0) {
            *FIELD(arg0, s8 **, 0x98) = 0;
        }
        func_80033D08(arg0);
        FIELD(arg0, u16 *, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return func_800A96F0();
    }
    if (state == 2) {
        func_80033D08(arg0);
        return func_800A96F0();
    }
    func_80033CD8(arg0, &D_800A9528);
    callback = FIELD(arg0, M2C_UNK (**)(void *, s32, M2C_UNK), 0x50);
    if (callback != 0) {
        callback(arg0, arg1, arg2);
    }
}
