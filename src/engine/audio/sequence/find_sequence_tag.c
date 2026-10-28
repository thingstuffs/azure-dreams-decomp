#include "common.h"
#include "engine/audio/sequence.h"
#include "slus/data.h"

/* D_80085FA4: [0] = base address of a byte table; accessed via %hi/%lo (forced size>8) */

/*
 * Searches the byte table for audio_sequence_track_tag's four bytes, returning the index after the
 * match or -1.
 *
 * audio_sequence_stream_limit: [0] = table length/bound; accessed via %hi/%lo (forced size>8)
 *
 * Fixed 4-byte data blob compared against entries in the audio_sequence_data_base[0] table.
 */
s32 find_sequence_tag(s32 start_index)
{
    s32 byte_index = start_index;

    do {
        if (compare_byte_span(audio_sequence_track_tag, audio_sequence_data_base[0] + byte_index, 4) == 0) {
            return byte_index + 4;
        }
        byte_index = byte_index + 1;
    } while ((u32)audio_sequence_stream_limit[0] >= (u32)byte_index);

    return -1;
}
