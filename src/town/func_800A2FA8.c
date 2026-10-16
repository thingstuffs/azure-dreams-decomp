#include "modules/town_door.h"

/* Clear and flag the object on a nonzero check result, or invoke its callback. */
void townHandleDoorCheckResult(S_func_800A0708_0 *object, void *callback_arg, s32 callback_data)
{
    s8 *linked_flag;
    s32 check_result;
    void (*callback)(void *, void *, void *, s32);

    check_result = townClassifyObjectAgainstBounds(object, callback_arg);
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
            objectFlagBlock.flags = (s32)(objectFlagBlock.flags | 0x8000);
            return;
        } else {
            register void *object_arg = callback_object;

            callback = callback_object->unk_50;
            callback(callback_object, object_arg, callback_arg, callback_data);
        }
    }
}
