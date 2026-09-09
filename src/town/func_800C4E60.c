#include "common.h"

typedef void (*Callback)(void *, s32, s32);

extern u32 func_8009CFE0(void *, s32);
extern void func_8008F134(void *);
extern void func_80033D08(void *);
extern s32 D_800814A0[];

/* Clears and flags the object when the check succeeds, or invokes its callback. */
void func_800C25C0(void *object, s32 check_value, s32 callback_value) {
    u16 *object_flags;
    s8 *status_byte;

    if (func_8009CFE0(object, check_value) != 0) {
        func_8008F134(object);
        status_byte = *(s8 **)((u8 *)object + 0x98);
        if (status_byte != 0) {
            *status_byte = 0;
        }
        func_80033D08(object);
        object_flags = (u16 *)object - 1;
        *object_flags |= 0x8000;
        D_800814A0[0] |= 0x8000;
    } else {
        (*(Callback *)((u8 *)object + 0x50))(object, check_value, callback_value);
    }
}
