#include "common.h"
#include "slus/audio_voice_data.h"
#include "engine/audio/slots.h"

/* The owner declaration's four entries exceed -G (8), so this access emits
 * %hi/%lo instead of a $gp-relative reference. This function writes entry 0. */
/* Records a level index from 1 through 24, or returns 0xFF if invalid. */
int set_audio_entry_count(int level_index) {
    level_index &= 0xFF;
    if ((unsigned)level_index >= 25)
        return 0xFF;
    if (level_index == 0)
        return 0xFF;
    audio_voice_count[0] = level_index;
    return level_index;
}
