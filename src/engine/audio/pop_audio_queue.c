#include "common.h"
#include "engine/audio.h"

/* FIFO pop from u16 queue at D_80084778: [0]=count (clamped to 0x20),
 * [1..]=entries. Shifts remaining entries left and decrements count. */

/* Pops the oldest queue entry and shifts the rest left, returning zero if empty. */
u16 pop_audio_queue(void)
{
    u16 entry;
    u16 i;

    if (audio_command_queue[0] > 0x20) {
        audio_command_queue[0] = 0x20;
    }
    entry = 0;
    if (audio_command_queue[0] != 0) {
        entry = audio_command_queue[1];
        for (i = 1; i < audio_command_queue[0]; i++) {
            audio_command_queue[i] = audio_command_queue[i + 1];
        }
        audio_command_queue[0] = audio_command_queue[0] - 1;
    }
    return entry;
}
