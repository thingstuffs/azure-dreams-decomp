#include "common.h"
#include "engine/audio.h"
#include "shared/dungeon_floor.h"
#include "slus/runtime_directory.h"

/* Return the current value capped at 40 when the mode is 2, or zero otherwise. */
s32 read_capped_audio_meter(void)
{
    if (runtime_dispatch_mode_alias[0] == 2) {
        s32 capped_value = 0x28;
        s32 current_value = floor_generation_state.floor_number;

        if (current_value < 0x29) {
            capped_value = current_value;
        }
        return capped_value;
    }
    return 0;
}
