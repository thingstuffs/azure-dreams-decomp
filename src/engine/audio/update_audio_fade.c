#include "shared/sound_state.h"
#include "common.h"
#include "engine/audio.h"

/* Raises or lowers the active gauge, calling its callback after an update or returning -1 on depletion. */
s32 update_audio_fade(SoundTask *gauge)
{
    u16 next_value;

    switch (gauge->unk_04) {
    case 1:
        next_value = (u16)(gauge->unk_08 + (u16)gauge->unk_16);
        gauge->unk_08 = next_value;
        if (gauge->unk_0A < (s16)next_value) {
            gauge->unk_08 = (s16)gauge->unk_0A;
            gauge->unk_04 = 3;
        }
        break;
    case 2:
        next_value = (u16)(gauge->unk_08 - (u16)gauge->unk_18);
        gauge->unk_08 = next_value;
        if ((s16)next_value <= 0) {
            gauge->unk_08 = 0;
            return -1;
        }
        break;
    default:
        return 0;
    }

    if (gauge->callback != 0) {
        gauge->callback();
    }
    return 0;
}
