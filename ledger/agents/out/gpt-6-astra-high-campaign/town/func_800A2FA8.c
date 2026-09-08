#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(base, type, offset) (*(type)((s8 *)(base) + (offset)))

extern void func_80033D08(void *arg0);
extern s32 func_8009CFE0(void *, M2C_UNK);
extern s32 D_800814A0[3];

/* Clear and flag the object on a nonzero check result, or invoke its callback. */
void func_800A0708(void *object, M2C_UNK callback_arg, M2C_UNK callback_data)
{
    s8 *linked_flag;
    M2C_UNK check_result;
    M2C_UNK (*callback)(void *, M2C_UNK, M2C_UNK, M2C_UNK);

    check_result = func_8009CFE0(object, callback_arg);
    {
        register void *callback_object = object;

        if (check_result != 0) {
            linked_flag = FIELD(object, s8 **, 0x98);
            if (linked_flag != 0) {
                *linked_flag = 0;
            }
            func_80033D08(object);
            FIELD(object, u16 *, -2) =
                (u16)(FIELD(object, u16 *, -2) | 0x8000);
            D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
            return;
        } else {
            register void *object_arg = callback_object;

            callback = FIELD(callback_object,
                             M2C_UNK (**)(void *, M2C_UNK, M2C_UNK,
                                           M2C_UNK),
                             0x50);
            callback(callback_object, object_arg, callback_arg, callback_data);
        }
    }
}
