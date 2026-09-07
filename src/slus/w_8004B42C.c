#include "common.h"

/* Fills arr[0..cnt) with results of func_8004B404(0x82); on first zero result, calls
   func_8004B248(arr) and returns NULL instead of the array pointer. */
extern s32 func_8004B404(s32 a0);
extern void func_8004B248(s32 *a0);

s32 *allocBufferArray(s32 *a0, s32 a1)
{
    s32 *arr = a0;
    s32 cnt = a1;
    s32 i;
    s32 v0;

    for (i = 0; i < cnt; i++)
    {
        v0 = func_8004B404(0x82);
        arr[i] = v0;
        if (v0 == 0)
        {
            func_8004B248(arr);
            arr = 0;
            break;
        }
    }
    return arr;
}
