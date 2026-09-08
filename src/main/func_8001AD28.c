#include "common.h"

s32 func_8007CA58();
s32 func_8007CA68();
s32 func_8007CA88();
void func_8007CA98();

/* Writes 128-byte blocks to a file, optionally creating it first. */
s32 func_8001AD28(s32 filename, void *buffer, s32 block_count, s32 block_offset, s32 skip_create) {
    s32 success;
    s32 fd;
    s32 byte_count;

    success = 0;
    if (skip_create == 0) {
        fd = func_8007CA58(filename, 0x30200);
        if (fd == -1) {
            goto done;
        }
        func_8007CA98(fd);
    }
    fd = func_8007CA58(filename, 2);
    if (fd != -1) {
        if ((block_offset == 0) || (func_8007CA68(fd, block_offset << 7, 0) != -1)) {
            byte_count = block_count << 7;
            if (func_8007CA88(fd, buffer, byte_count) == byte_count) {
                success = 1;
            }
        }
        func_8007CA98(fd);
    }
done:
    return success;
}
