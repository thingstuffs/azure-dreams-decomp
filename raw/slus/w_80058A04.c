#include "common.h"

extern int func_800589B8(int a0);

/* Reads a variable-length (LEB128-style) integer from the stream object
 * pointed to by a0 via repeated calls to func_800589B8: the first byte's
 * low 7 bits seed the accumulator (or the whole byte if its MSB is clear,
 * meaning a single-byte value), then each subsequent byte (while its MSB
 * is set) shifts the accumulator left 7 bits and adds in that byte's
 * low 7 bits. Returns 0 immediately if the first read yields 0. */
s32 func_80058A04(s32 a0)
{
    s32 v0;
    s32 s0;

    v0 = func_800589B8(a0);
    if (v0 == 0)
    {
        return 0;
    }
    s0 = v0;
    if (!(s0 & 0x80))
    {
        return s0;
    }
    s0 = s0 & 0x7F;
    do
    {
        v0 = func_800589B8(a0);
        s0 = (s0 << 7) + (v0 & 0x7F);
    } while (v0 & 0x80);
    return s0;
}
