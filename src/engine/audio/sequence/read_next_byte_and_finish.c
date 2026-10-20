#include "common.h"



extern s32 audio_sequence_data_base[4];
extern s32 audio_sequence_stream_limit[4];

typedef struct {
    s32 unk00;
    u8 pad04[0x28];
    s32 unk2C;
} S_800589B8;

/* Read the next byte and mark the reader finished if its position exceeds the limit. */
s32 read_next_byte_and_finish(S_800589B8 *reader)
{
    s32 position;
    s32 byte_value;
    s32 byte_count;

    byte_value = ((u8 *)audio_sequence_data_base[0])[reader->unk00];
    position = reader->unk00;
    byte_count = audio_sequence_stream_limit[0];
    position = position + 1;
    reader->unk00 = position;
    if ((u32)byte_count < (u32)position) {
        reader->unk2C = 1;
        return -1;
    }
    return byte_value;
}
