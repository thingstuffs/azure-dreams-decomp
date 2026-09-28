#include "common.h"

#include "common.h"

extern s32 D_80085FA4[4];
extern s32 D_800869B0[4];

typedef struct {
    s32 unk00;
    u8 pad04[0x28];
    s32 unk2C;
} S_800589B8;

/* Read the next byte and mark the reader finished if its position exceeds the limit. */
s32 func_800589B8(S_800589B8 *reader)
{
    s32 position;
    s32 byte_value;
    s32 byte_count;

    byte_value = ((u8 *)D_80085FA4[0])[reader->unk00];
    position = reader->unk00;
    byte_count = D_800869B0[0];
    position = position + 1;
    reader->unk00 = position;
    if ((u32)byte_count < (u32)position) {
        reader->unk2C = 1;
        return -1;
    }
    return byte_value;
}
