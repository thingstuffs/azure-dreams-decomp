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
    S_800589B8 *read_state = reader;
    register u32 limit_page ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u8 *data;
    s32 position;
    s32 byte_value;
    s32 byte_count;

    data = (u8 *)D_80085FA4[0];
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    position = read_state->unk00;
    limit_page = 0x80080000;
    byte_value = data[position];
    byte_count = *(s32 *)(limit_page + 0x69B0);
    position = position + 1;
    read_state->unk00 = position;
    if ((u32)byte_count < (u32)position) {
        read_state->unk2C = 1;
        return -1;
    }
    ASM_USE(limit_page);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    return byte_value;
}
