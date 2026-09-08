#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u32 D_80175D58[3];

/* Returns whether the selected word in D_80175D58 is zero. */
s32 func_8016F908(s32 use_second_word) {
    if (use_second_word != 0) {
        volatile u8 *page = (volatile u8 *)0x80170000;
        return *(volatile u32 *)(page + 0x5D5C) == 0;
    }
    return D_80175D58[0] == 0;
}
