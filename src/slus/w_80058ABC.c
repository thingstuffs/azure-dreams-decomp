#include "common.h"

extern s32 slusReadNextByteAndFinish(s32 a0);
extern u32 packBigEndianWord(s32 a0, s32 a1, s32 a2, s32 a3);

/* Reads four bytes from the stream and packs them into a word. */
u32 readBigEndianWord(s32 stream)
{
    s32 first_byte, second_byte, third_byte, fourth_byte;

    first_byte = slusReadNextByteAndFinish(stream);
    second_byte = slusReadNextByteAndFinish(stream);
    third_byte = slusReadNextByteAndFinish(stream);
    fourth_byte = slusReadNextByteAndFinish(stream);
    return packBigEndianWord(first_byte & 0xFF, second_byte & 0xFF, third_byte & 0xFF, fourth_byte & 0xFF);
}
