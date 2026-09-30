#include "common.h"

/* D_80081480 / D_8008148C / D_80080A7C are 4-byte words (retail neighbours D_80081485 /
 * D_80081490 / D_80080A80 bound them). */
extern s32 D_80081480;
extern s32 D_8008148C;
extern s32 D_80080A7C;

extern s32 DrawSync(s32 a0);

/* Reserves bytes from the buffer's end, resetting its write pointer and waiting for the GPU on overlap. */
s32 func_800405E8(s32 byte_count)
{
    s32 reserved_start;
    s32 remaining_size;
    s32 buffer_base;
    s32 buffer_end;

    buffer_base = D_8008148C;
    buffer_end = buffer_base + D_80080A7C;
    if ((u32)(D_80081480 + byte_count) >= (u32)buffer_end) {
        D_80081480 = buffer_base;
        DrawSync(0);
    }
    {
        s32 current_base = D_8008148C;
        remaining_size = D_80080A7C;
        reserved_start = current_base + remaining_size;
    }
    reserved_start = reserved_start - byte_count;
    D_80080A7C = remaining_size - byte_count;
    return reserved_start;
}
