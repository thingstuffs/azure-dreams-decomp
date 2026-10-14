#include "modules/ovmovie_libpress.h"
/* Wait for output DMA completion, resetting the decoder on timeout. */
static s32 func_80177C58(void) {
    volatile s32 polls_left = 0x100000;
    if (*D_80178360 & 0x01000000) {
        do {
            if (--polls_left == -1) {
                func_80177D08((const char *)&D_8017682C);
                return -1;
            }
        } while (*D_80178360 & 0x01000000);
    }
    return 0;
}
