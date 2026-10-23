#include "common.h"
#include "engine/audio.h"
#include "slus.h"



extern unsigned char runtime_dispatch_mode_alias[9];

/*
 * Sends the low 16 bits to SD_Call unless runtime_dispatch_mode_alias is 2; returns zero when
 * disabled.
 */
short dispatch_sound_word_unless_disabled(int inputValue)
{
    if (runtime_dispatch_mode_alias[0] != 2) {
        return SD_Call((unsigned short)inputValue);
    }

    return 0;
}
