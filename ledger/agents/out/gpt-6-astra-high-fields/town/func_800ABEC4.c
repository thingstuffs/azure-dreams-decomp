#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_func_800A9624_1 {
    u8 pad_00[0x50];
    M2C_UNK (*unk_50)(void *, s32, M2C_UNK);
    u8 pad_54[0x44];
    s8 *unk_98;
} S_func_800A9624_1;

extern M2C_UNK func_80033CD8();
extern M2C_UNK func_80033D08();
extern s32 func_8009D20C(void *, s32);
extern M2C_UNK func_800A8BBC();
extern s32 D_800814A0;
extern M2C_UNK D_800A9528;

/* Process object state results or invoke the fallback callback. */
void func_800A9624(S_func_800A9624_1 *object, s32 state_arg, M2C_UNK callback_arg) {
    s32 state;
    M2C_UNK (*callback)(void *, s32, M2C_UNK);

    state = func_8009D20C(object, state_arg);
    if (state == 1) {
        func_800A8BBC(0x1B, 0x1C, 0x1D, 0x1E, state_arg);
        if (object->unk_98 != 0) {
            *object->unk_98 = 0;
        }
        func_80033D08(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }
    if (state == 2) {
        func_80033D08(object);
        return;
    }
    func_80033CD8(object, &D_800A9528);
    callback = object->unk_50;
    if (callback != 0) {
        callback(object, state_arg, callback_arg);
    }
}
