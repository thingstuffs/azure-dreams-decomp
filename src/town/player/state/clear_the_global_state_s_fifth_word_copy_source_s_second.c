#include "common.h"

extern s32 D_800FE5C0[];

/* Clear the global state's fifth word and copy the source's second word. */
void clear_the_global_state_s_fifth_word_copy_source_s_second(s32 *source) {
    D_800FE5C0[4] = 0;
    D_800FE5C0[1] = source[1];
}
