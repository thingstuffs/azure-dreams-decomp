#include "common.h"

/* Copy records through the end marker and return the next destination slot. */
void *func_800B1434(void *dest, void *src) {
    void *src_tail = src + 8;
    void *dest_tail = dest + 8;

    do {
        *(s32 *)dest = *(s32 *)src;
        *(s32 *)(dest + 4) = *(s32 *)(src + 4);
        *(s32 *)(dest + 8) = *(s32 *)(src + 8);
        dest += 0xC;
        if (*(s8 *)src < 0) {
            return dest;
        }
        dest_tail += 0xC;
        src_tail += 0xC;
        src += 0xC;
    } while (1);
}
