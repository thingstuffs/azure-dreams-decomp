#include "common.h"

extern u32 func_80019C68(s32 arg0, s32 arg1);
extern void func_8001AD60(s32 arg0);
extern u8 D_8001F15A[];

/* Record whether the check returned zero and invoke the handler when it did. */
s32 func_80017F3C(s32 check_input_1, s32 check_input_2) {
    s32 result;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

    result = func_80019C68(check_input_1, check_input_2);
    if (result == 0)
        goto zero_result;
    D_8001F15A[0] = 0;
    goto done;
zero_result:
       /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    D_8001F15A[0] = 1;
    func_8001AD60(0xD7A);
done:
    return result;
}
