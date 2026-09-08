#include "common.h"

extern int func_800589B8(int a0);

/* Reads a variable-length integer from the stream, most significant 7-bit group first. */
s32 func_80058A04(s32 stream)
{
    s32 byte;
    s32 value;

    byte = func_800589B8(stream);
    if (byte == 0)
    {
        return 0;
    }
    value = byte;
    if (!(value & 0x80))
    {
        return value;
    }
    value = value & 0x7F;
    do
    {
        byte = func_800589B8(stream);
        value = (value << 7) + (byte & 0x7F);
    } while (byte & 0x80);
    return value;
}
