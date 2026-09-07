#include "common.h"

#include "common.h"

extern void *func_8003ACC0(u8 *buf, u16 len);

u8 *func_8003AD08(u32 value, u8 *out)
{
    u8 digits[16];
    u8 *digit = digits;
    s32 count = 0;

    do {
        *digit = value % 10;
        count++;
        value /= 10;
        digit++;
    } while (value != 0);

    digit = func_8003ACC0(digits, count);
    do {
        *out++ = 0x82;
        *out++ = *digit++ + 0x4F;
        count--;
    } while (count > 0);
    *out = 0;
    return out;
}
