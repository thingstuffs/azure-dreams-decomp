#include "common.h"

extern s32 D_80175D48;

#ifndef NON_MATCHING
extern u8 D_04816000;
__asm__(".set D_04816000, 0x04816000");
#define INITIAL_VALUE ((s32)&D_04816000)
#else
#define INITIAL_VALUE 0x04816000
#endif

/* Sets the global word pair to a fixed value and nine times the input plus an offset. */
void func_8016F834(s32 input_value) {
    s32 word_value;
    s32 *state_words;

    do {
        D_80175D48 = INITIAL_VALUE;
    } while (0);
    word_value = D_80175D48;

    state_words = &D_80175D48;

    word_value = (input_value * 9) + 0x30B2;
    state_words[1] = word_value;
}
