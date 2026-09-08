#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(base, type, offset) (*(type)((s8 *)(base) + (offset)))

extern s32 func_8009CFE0(void *, M2C_UNK);
extern void func_80033D08(void *arg0);
extern s32 D_800814A0[3];

/* Clears and marks a handled object, or dispatches to its callback. */
void func_800A6C4C(void *object, M2C_UNK input, M2C_UNK callback_data) {
    s8 *status_flag;
    M2C_UNK (*callback)(void *, M2C_UNK, M2C_UNK);

    if (func_8009CFE0(object, input) != 0) {
        status_flag = FIELD(object, s8 **, 0x98);
        if (status_flag != 0) {
            *status_flag = 0;
        }
        func_80033D08(object);
        FIELD(object, u16 *, -2) = (u16) (FIELD(object, u16 *, -2) | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
        return;
    }

    callback = FIELD(object, M2C_UNK (**)(void *, M2C_UNK, M2C_UNK), 0x50);
    if (callback != 0) {
        callback(object, input, callback_data);
    }
}
