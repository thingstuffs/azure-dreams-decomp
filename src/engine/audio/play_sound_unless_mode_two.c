#include "common.h"



extern unsigned char runtime_dispatch_mode_alias[9];
extern short SD_Call(int a0);

// Forwards the low 16 bits of the input when D_80082E6A[0] is not 2.
short dispatch_sound_word_unless_disabled(int inputValue)
{
    if (runtime_dispatch_mode_alias[0] != 2) {
        return SD_Call((unsigned short)inputValue);
    }

    return 0;
}
