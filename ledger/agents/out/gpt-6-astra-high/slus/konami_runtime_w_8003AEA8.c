#include "common.h"

#include "common.h"

/* Zero the requested number of 32-bit words. */
void func_8003AEA8(s32 *words, s32 count) {
    s32 *word;
    s32 remaining;

    word = words;
    remaining = count;
    if (remaining > 0) {
        do {
            *word = 0;
            remaining -= 1;
            word += 1;
        } while (remaining > 0);
    }
}
