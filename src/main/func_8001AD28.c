#include "common.h"

s32 func_8007CA58();
s32 func_8007CA68();
s32 func_8007CA88();
void func_8007CA98();

s32 func_8001AD28(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 result;
    s32 fd;
    s32 size;

    result = 0;
    if (arg4 == 0) {
        fd = func_8007CA58(arg0, 0x30200);
        if (fd == -1) {
            goto done;
        }
        func_8007CA98(fd);
    }
    fd = func_8007CA58(arg0, 2);
    if (fd != -1) {
        if ((arg3 == 0) || (func_8007CA68(fd, arg3 << 7, 0) != -1)) {
            size = arg2 << 7;
            if (func_8007CA88(fd, arg1, size) == size) {
                result = 1;
            }
        }
        func_8007CA98(fd);
    }
done:
    return result;
}
