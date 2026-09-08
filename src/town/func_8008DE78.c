#include "common.h"

extern s8 D_800CFC24[];
extern void func_80035208(s8 *);

/* Pack a value in little-endian order and a code into the shared buffer and submit it. */
void func_8008B5D8(s32 value, s8 code) {
    s8 *buffer = (s8 *)D_800CFC24;

    buffer[3] = value >> 8;
    buffer[2] = value;
    buffer[4] = value >> 16;
    buffer[5] = value >> 24;
    buffer[6] = code;
    func_80035208(buffer);
}
