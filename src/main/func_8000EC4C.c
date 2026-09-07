#include "common.h"

extern s32 open();
extern s32 lseek();
extern s32 write();
extern s32 close();

s32 func_80021C4C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 fd;
    s32 ok;

    ok = 0;
    if (arg4 == 0) {
        fd = open(arg0, 0x30200);
        if (fd == -1) {
            return ok;
        }
        close(fd);
    }

    fd = open(arg0, 2);
    if (fd == -1) {
        return ok;
    }

    if ((arg3 == 0) || (lseek(fd, arg3 << 7, 0) != -1)) {
        s32 sz = arg2 << 7;
        if (write(fd, arg1, sz) == sz) {
            ok = 1;
        }
    }
    close(fd);
    return ok;
}
