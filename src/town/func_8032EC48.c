#include "common.h"

/* Copy a zero-terminated string and return the destination. */
u8 *func_80019448(u8 *destination, u8 *source) {
    u8 *destination_start;
    u8 *write_ptr;
    u8 *read_ptr;

    write_ptr = destination;
    read_ptr = source;
    destination_start = write_ptr;
    if (*read_ptr != 0) {
        do {
            do { *write_ptr = *read_ptr; } while (0);
            read_ptr += 1;
            write_ptr += 1;
        } while (*read_ptr != 0);
    }
    *write_ptr = 0;
    return destination_start;
}
