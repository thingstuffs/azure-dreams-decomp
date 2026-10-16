/* Relink of matched town/func_8032EBF4; every changed retail word is a paired relocation. */
#define townClearBytes func_80018824
#include "common.h"

/* Clears length bytes in the buffer and returns the buffer. */
s8 *func_80018824(s8 *buffer, s32 length) {
    s32 index;

    index = 0;
    if (length > 0) {
        do {
            *(buffer + index) = 0;
            index += 1;
        } while (index < length);
    }
    return buffer;
}
