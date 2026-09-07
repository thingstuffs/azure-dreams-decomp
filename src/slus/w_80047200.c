#include "common.h"

#include "common.h"

void func_80047200(u16 *arg0, s32 arg1, s32 arg2)
{
    register s32 i;
    register s32 j;

    j = 1;
    if (arg2 == 0) {
        i = 0;
        if (arg1 > 0) {
            do {
                arg0++;
                for (j = 1; j < 0x10; j++) {
                    *arg0 |= 0x8000;
                    arg0++;
                }
                i++;
            } while (i < arg1);
        }
    } else {
        for (; j < 0x100; j++) {
            *arg0 |= 0x8000;
            arg0++;
        }
    }
}
