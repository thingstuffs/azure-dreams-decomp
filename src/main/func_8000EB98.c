#include "common.h"

extern s32 open(s32 arg0, s32 arg1);
extern s32 lseek(s32 arg0, s32 arg1, s32 arg2);
extern s32 read(s32 arg0, s32 arg1, s32 arg2);
extern void close(s32 arg0);

/* Reads a file range in 128-byte units and returns whether the full read succeeded. */
s32 func_80021B98(s32 path, s32 buffer, s32 read_size, s32 block_offset) {
    register s32 success ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 fd;

    success = 0;
    fd = open(path, 1);
    if (fd != -1) {
        read_size <<= 7;
        if ((block_offset == 0) || (lseek(fd, block_offset << 7, success) != -1)) {
            success = read(fd, buffer, read_size) == read_size;
        }
        close(fd);
    }
    return success;
}
