#include "common.h"

s32 func_8007CA58();
s32 func_8007CA68();
s32 func_8007CA78();
void func_8007CA98();

/* Reads a file range in 128-byte units and returns whether the full read succeeded. */
s32 func_8001AC70(s32 file_path, void *buffer, s32 block_count, s32 block_offset) {
    s32 fd;
    s32 success;
    s32 byte_count;
    s32 error;

    success = 0;
    fd = func_8007CA58(file_path, 1);
    error = -1;
    if (fd != error) {
        byte_count = block_count << 7;
        if (block_offset == 0 || func_8007CA68(fd, block_offset << 7, 0) != error) {
            if (func_8007CA78(fd, buffer, byte_count) == byte_count) {
                success = 1;
            }
        }
        func_8007CA98(fd);
    }
    return success;
}
