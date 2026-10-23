#include "shared/sound_state.h"
#include "common.h"
#include "engine/audio.h"
#include "slus/data.h"

/*
 * Fires event 0x74 when the CD read position reaches its target or the pending read check fails.
 *
 * The shared task record is passed to the pending-read check.
 *
 * Declared as an array (>8B) so gcc emits %hi/%lo addressing (lui+lw), matching the target's lui
 * v1,%hi(cd_stream_end_sector); lw v1,%lo(cd_stream_end_sector)(v1) sequence.
 */
void check_cd_stream_end(void) {
    if ((u32)sound_get_cd_sector_position() < cd_stream_end_sector[0]) {
        if (update_audio_fade(&sound_stream_task) == -1) {
            audio_handle_stream_control_event(0x74);
        }
    } else {
        audio_handle_stream_control_event(0x74);
    }
}
