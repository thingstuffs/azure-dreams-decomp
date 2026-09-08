#include "common.h"

extern s32 open(s32 arg0, s32 arg1);
extern s32 lseek(s32 arg0, s32 arg1, s32 arg2);
extern s32 read(s32 arg0, s32 arg1, s32 arg2);
extern void close(s32 arg0);

s32 func_80021B98(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    register s32 ret ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 fd;

    ret = 0;
    fd = open(arg0, 1);
    if (fd != -1) {
        arg2 <<= 7;
        if ((arg3 == 0) || (lseek(fd, arg3 << 7, ret) != -1)) {
            ret = read(fd, arg1, arg2) == arg2;
        }
        close(fd);
    }
    return ret;
}
