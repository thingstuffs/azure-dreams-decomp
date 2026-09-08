#include "common.h"

extern void func_800AAE30(void *, s32, s32 *);
extern s32 D_800834B8;
extern u8 D_800AA5F8[];
extern s32 *D_800D0B14;
extern u16 D_80100D62;

/* Copy global state into the object and values, then conditionally call func_800AAE30. */
void func_800AAD3C(void *object, s32 call_arg, s32 *values) {
    u16 saved_value = D_80100D62;
    s32 *saved_values = D_800D0B14;

    *(u16 *)((u8 *)object + 0x72) = saved_value;
    if (saved_values != 0) {
        values[0] = saved_values[0];
        values[1] = saved_values[1];
        values[2] = saved_values[2];
    }

    if (D_800834B8 != (s32)D_800AA5F8) {
        func_800AAE30(object, call_arg, values);
    }
}
