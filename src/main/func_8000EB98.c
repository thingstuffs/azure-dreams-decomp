#include "modules/main_server_ship.h"
#include "common.h"

extern s32 open(s32 path, s32 flags);
extern s32 lseek(s32 fd, s32 offset, s32 whence);
extern s32 read(s32 fd, s32 buffer, s32 count);

/* Reads a file range in 128-byte units and returns whether the full read succeeded. */
s32 card_boot_read_file_units_128(s32 path, s32 buffer, s32 read_size, s32 block_offset) {
    s32 success;
    s32 fd;

    success = 0;
    fd = open(path, 1);
    if (fd != -1) {
        read_size <<= 7;
        if ((block_offset == 0) || (lseek(fd, block_offset << 7, success) != -1)) {
            success = read(fd, buffer, read_size);
            success = success == read_size;
        }
        close(fd);
    }
    return success;
}
