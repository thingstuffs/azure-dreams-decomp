#include "common.h"
#include "engine/audio/sequence.h"
#include "slus/data.h"

/* D_80085FA4: accessed via %hi/%lo (not gp_rel) in this and sibling funcs
 * (read_next_byte_and_finish, func_800599B0, func_80058850, init_sequence_playback) -> declare size > 8 bytes.
 * Holds a byte-pointer value (base address of a working buffer). */
extern s32 audio_sequence_data_base[4];

/*
 * Compares audio_sequence_entry_marker at successive offsets through the unsigned stream limit,
 * returning the offset just past the three-byte match or -1.
 *
 * audio_sequence_stream_limit and audio_sequence_entry_marker are declared larger than eight bytes
 * to retain hi/lo addressing rather than gp-relative accesses. The former holds the unsigned scan
 * limit; the latter supplies the three marker bytes.
 */
s32 scan_stream_for_three_byte_marker(s32 offset)
{
    s32 comparison;

    do {
        comparison = compare_byte_span(audio_sequence_entry_marker, (u8 *)audio_sequence_data_base[0] + offset, 3);
        if (comparison == 0) {
            return offset + 3;
        }
        offset++;
    } while ((u32)offset <= (u32)audio_sequence_stream_limit[0]);
    return -1;
}
