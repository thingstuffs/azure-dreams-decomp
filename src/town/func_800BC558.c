#include "common.h"

extern s32 func_8009CFE0(void *, void *);
extern void func_80033D08(void *arg0);
extern s32 D_800814A0[3];

/* Clear the object's linked flag and mark completion, or advance its wrapped angle. */
void func_800B9CB8(void *object, void *context)
{
    u8 *linked_flag;

    if (func_8009CFE0(object, context) != 0) {
        linked_flag = *(u8 **)((u8 *)object + 0x98);
        if (linked_flag != 0) {
            *linked_flag = 0;
        }
        func_80033D08(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    *(u16 *)((u8 *)object + 0x66) =
        *(u16 *)((u8 *)object + 0x66) + *(s8 *)((u8 *)object + 0x97);
    *(s16 *)((u8 *)object + 0x66) %= 0x1000;
}
