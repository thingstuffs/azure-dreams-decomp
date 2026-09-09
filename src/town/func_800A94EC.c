#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_func_800A6C4C_0 {
    u8 pad_00[0x50];
    M2C_UNK (*unk_50)(void *, M2C_UNK, M2C_UNK);
    u8 pad_54[0x44];
    s8 *unk_98;
} S_func_800A6C4C_0;

typedef struct S_func_800A6C4C_1 {
    u16 unk_00;
} S_func_800A6C4C_1;

extern s32 func_8009CFE0(void *, M2C_UNK);
extern void func_80033D08(void *arg0);
extern s32 D_800814A0[3];

/* Clears and marks a handled object, or dispatches to its callback. */
void func_800A6C4C(S_func_800A6C4C_0 *object, M2C_UNK input, M2C_UNK callback_data) {
    s8 *status_flag;
    M2C_UNK (*callback)(void *, M2C_UNK, M2C_UNK);

    if (func_8009CFE0(object, input) != 0) {
        status_flag = object->unk_98;
        if (status_flag != 0) {
            *status_flag = 0;
        }
        func_80033D08(object);
        ((S_func_800A6C4C_1 *)((u8 *)object - 2))->unk_00 = (u16) (((S_func_800A6C4C_1 *)((u8 *)object - 2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
        return;
    }

    callback = object->unk_50;
    if (callback != 0) {
        callback(object, input, callback_data);
    }
}
