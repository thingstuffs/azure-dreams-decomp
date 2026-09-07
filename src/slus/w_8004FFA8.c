#include "common.h"

extern s32 func_8004FF20(void *a0);
extern void func_80050EA8(void *a0);

/* Checks sub-state via func_8004FF20; if non-zero, restores the saved
 * callback (a0->unk_04) into a0->unk_neg10 and runs the cleanup routine
 * func_80050EA8 on the nested sub-struct at a0-0x20. Returns the check result. */
s32 func_8004FFA8(void *a0)
{
    s32 s1 = func_8004FF20(a0);

    if (s1 != 0) {
        *(s32 *)((u8 *)a0 - 0x10) = *(s32 *)((u8 *)a0 + 0x4);
        func_80050EA8((u8 *)a0 - 0x20);
    }
    return s1;
}
