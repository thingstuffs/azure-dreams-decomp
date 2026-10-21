#include "common.h"
#include "engine/util.h"

/* Reverses len bytes in place and returns the original buffer pointer. */
void *reverse_bytes(u8 *buf, u16 len)
{
    u8 *start = buf;
    u8 *end = start + (len - 1);
    while (buf < end) {
        u8 front_byte = *buf;
        u8 back_byte = *end;
        *end = front_byte;
        end--;
        *buf = back_byte;
        buf++;
    }
    return start;
}
