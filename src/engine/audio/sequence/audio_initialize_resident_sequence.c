#include "common.h"
#include "engine/audio/sequence.h"
#include "slus/data.h"

/* extern/typedef decls */
/* D_80085FA4: accessed via %hi/%lo (not gp_rel) in this and sibling funcs
 * (read_next_byte_and_finish, func_800599B0, scan_stream_for_three_byte_marker, init_sequence_playback) -> declare size > 8 bytes. */
extern s32 audio_sequence_data_base[4];

/* D_800869B0: accessed via %hi/%lo (not gp_rel) in this and sibling funcs
 * (read_next_byte_and_finish, scan_stream_for_three_byte_marker, init_sequence_playback) -> declare size > 8 bytes. */

/* D_800737A4: hi/lo access -> size must be > 8 bytes (see func_800584E4 in src/code.c) */
extern s32 audio_sequence_active[4];

/* Sets the byte table base and bound, initializes two subsystems, and marks them active. */
void audio_initialize_resident_sequence(void)
{
    audio_sequence_data_base[0] = 0x80080000;
    audio_sequence_stream_limit[0] = 0xC000;
    audio_reset_all_voices();
    func_800599B0();
    audio_sequence_active[0] = 1;
}
