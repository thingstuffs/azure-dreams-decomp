#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80033CD8();
extern M2C_UNK func_80033D08();
extern s32 func_8009D20C(void *, s32);
extern M2C_UNK func_800A8BBC();
extern s32 D_800814A0;
extern M2C_UNK D_800A9528;

#define FIELD(base, type, offset) (*(type)((s8 *)(base) + (offset)))

/* Process object state results or invoke the fallback callback. */
void func_800A9624(void *object, s32 state_arg, M2C_UNK callback_arg) {
    s32 state;
    M2C_UNK (*callback)(void *, s32, M2C_UNK);

    state = func_8009D20C(object, state_arg);
    if (state == 1) {
        func_800A8BBC(0x1B, 0x1C, 0x1D, 0x1E, state_arg);
        if (FIELD(object, s8 **, 0x98) != 0) {
            *FIELD(object, s8 **, 0x98) = 0;
        }
        func_80033D08(object);
        FIELD(object, u16 *, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }
    if (state == 2) {
        func_80033D08(object);
        return;
    }
    func_80033CD8(object, &D_800A9528);
    callback = FIELD(object, M2C_UNK (**)(void *, s32, M2C_UNK), 0x50);
    if (callback != 0) {
        callback(object, state_arg, callback_arg);
    }
}
