#include "common.h"

#include "common.h"

extern void func_8003AB44(u8 *arg0, s16 arg1, s16 arg2, s32 arg3,
                          s16 arg4, s32 arg5, s32 arg6);

void func_8003AC1C(s32 arg0, s32 arg1, s32 arg2, u8 *arg3)
{
    u8 *cursor = arg3;
    s32 i = 0;
    s32 selector = arg2;

    if (*cursor == 0) {
        return;
    }

    do {
        func_8003AB44(cursor, (s16)i, 0, selector & 0xFF,
                      (s16)arg0, (s16)arg1, 1);
        cursor += 2;
        i++;
    } while (*cursor != 0);
}
