#include "common.h"

s32 func_8007CA58();
s32 func_8007CA68();
s32 func_8007CA78();
void func_8007CA98();

s32 func_8001AC70(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 fd;
    s32 result;
    s32 size;
    s32 bad;

    result = 0;
    fd = func_8007CA58(arg0, 1);
    bad = -1;
    if (fd != bad) {
        size = arg2 << 7;
        if (arg3 == 0 || func_8007CA68(fd, arg3 << 7, 0) != bad) {
            if (func_8007CA78(fd, arg1, size) == size) {
                result = 1;
            }
        }
        func_8007CA98(fd);
    }
    return result;
}
