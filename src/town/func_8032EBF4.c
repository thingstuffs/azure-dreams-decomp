#include "common.h"

/* Clears length bytes in the buffer and returns the buffer. */
s8 *func_800193F4(s8 *buffer, s32 length) {
    s32 index;

    index = 0;
    if (length > 0) {
        do {
            *(buffer + index) = 0;
            index += 1;
        } while (index < length);
    }
    return buffer;
}
