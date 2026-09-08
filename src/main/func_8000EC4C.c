#include "common.h"

extern s32 open();
extern s32 lseek();
extern s32 write();
extern s32 close();

/* Writes 128-byte units at a file offset, optionally creating the file first. */
s32 func_80021C4C(s32 path, s32 buffer, s32 unit_count, s32 unit_offset, s32 skip_create) {
    s32 fd;
    s32 ok;

    ok = 0;
    if (skip_create == 0) {
        fd = open(path, 0x30200);
        if (fd == -1) {
            return ok;
        }
        close(fd);
    }

    fd = open(path, 2);
    if (fd == -1) {
        return ok;
    }

    if ((unit_offset == 0) || (lseek(fd, unit_offset << 7, 0) != -1)) {
        s32 byte_count = unit_count << 7;
        if (write(fd, buffer, byte_count) == byte_count) {
            ok = 1;
        }
    }
    close(fd);
    return ok;
}
