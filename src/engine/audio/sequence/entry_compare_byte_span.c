#include "common.h"
#include "engine/audio/sequence.h"
#include "slus/data.h"

/* S_80085FA4: array whose element 0 is a base address (cast to byte pointer for
 * pointer arithmetic in func_80058850, and set from a literal 0x80080000 address
 * value in audio_initialize_resident_sequence). */
extern s32 audio_sequence_data_base[4];

/*
 * Searches from start_index for audio_sequence_header_tag's four bytes, returning the index after
 * the match or -1.
 *
 * S_800869B0: array whose element 0 is a size/count value (unsigned compare against a running
 * index in find_sequence_magic_after_offset; set to 0xC000 in audio_initialize_resident_sequence).
 *
 * Fixed 4-byte data blob compared against entries in the audio_sequence_data_base[0] table.
 */
s32 find_sequence_magic_after_offset(s32 start_index)
{
    s32 byte_index = start_index;

    do {
        if (compare_byte_span(audio_sequence_header_tag, (s8 *)audio_sequence_data_base[0] + byte_index, 4) == 0) {
            return byte_index + 4;
        }
        byte_index = byte_index + 1;
    } while ((u32)audio_sequence_stream_limit[0] >= (u32)byte_index);

    return -1;
}
