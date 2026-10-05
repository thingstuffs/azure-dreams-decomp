#include "common.h"
#include "shared/object_flags.h"

extern s32 func_8009CFE0(void *object, s32 position_data);
extern void func_80033D08(void *arg0);


/* Finalizes and flags the object when its check succeeds or its countdown expires. */
void func_800A7C0C(void *object, s32 check_value)
{
    void *linked_flag;
    u16 ticks_left;

    if (func_8009CFE0(object, check_value) != 0) {
        linked_flag = *(void **)((u8 *)object + 0x98);
        if (linked_flag != 0) {
            *(u8 *)linked_flag = 0;
        }
    } else {
        ticks_left = *(u16 *)((u8 *)object + 0x6C) - 1;
        *(u16 *)((u8 *)object + 0x6C) = ticks_left;
        if ((s16)ticks_left > 0) {
            return;
        }
    }

    func_80033D08(object);
    *(u16 *)((u8 *)object - 2) |= 0x8000;
    objectFlagBlock.flags |= 0x8000;
}
