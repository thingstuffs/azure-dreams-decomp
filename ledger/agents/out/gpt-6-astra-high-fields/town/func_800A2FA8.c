#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_func_800A0708_0 {
    u8 pad_00[0x50];
    M2C_UNK (*unk_50)(void *, M2C_UNK, M2C_UNK, M2C_UNK);
    u8 pad_54[0x44];
    s8 *unk_98;
} S_func_800A0708_0;

typedef struct S_func_800A0708_1 {
    u16 unk_00;
} S_func_800A0708_1;

extern void func_80033D08(void *arg0);
extern s32 func_8009CFE0(void *, M2C_UNK);
extern s32 D_800814A0[3];

/* Clear and flag the object on a nonzero check result, or invoke its callback. */
void func_800A0708(S_func_800A0708_0 *object, M2C_UNK callback_arg, M2C_UNK callback_data)
{
    s8 *linked_flag;
    M2C_UNK check_result;
    M2C_UNK (*callback)(void *, M2C_UNK, M2C_UNK, M2C_UNK);

    check_result = func_8009CFE0(object, callback_arg);
    {
        register S_func_800A0708_0 *callback_object = object;

        if (check_result != 0) {
            linked_flag = object->unk_98;
            if (linked_flag != 0) {
                *linked_flag = 0;
            }
            func_80033D08(object);
            ((S_func_800A0708_1 *)((u8 *)object - 2))->unk_00 =
                (u16)(((S_func_800A0708_1 *)((u8 *)object - 2))->unk_00 | 0x8000);
            D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
            return;
        } else {
            register void *object_arg = callback_object;

            callback = callback_object->unk_50;
            callback(callback_object, object_arg, callback_arg, callback_data);
        }
    }
}
