#include "common.h"

extern void func_8004B1A4(u16 *a0);

/* Clear each non-null entry of a pointer array, flagging it via func_8004B1A4 first. */
void func_8004B1DC(u16 **arr, s32 count)
{
    s32 i;

    for (i = 0; i < count; i++) {
        if (arr[i] != 0) {
            func_8004B1A4(arr[i]);
            arr[i] = 0;
        }
    }
}
