#include "common.h"

#include "common.h"

/* Reverse the buffer bytes in place and return the original buffer pointer. */
void *func_8003ACC0(u8 *buffer, u16 length)
{
    u8 *buffer_start = buffer;
    u8 *last_byte = buffer_start + (length - 1);
    while (buffer < last_byte) {
        u8 front_byte = *buffer;
        u8 back_byte = *last_byte;
        *last_byte = front_byte;
        last_byte--;
        *buffer = back_byte;
        buffer++;
    }
    return buffer_start;
}
