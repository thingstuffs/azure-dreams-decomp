#include "common.h"

extern void func_800ADB30(void *arg0);
extern s32 D_800ADD80[4];

#ifndef NON_MATCHING
register u8 *dispatch_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#endif

/* Decrement the countdown and select the next dispatch when it expires. */
void func_800AE090(void *state_data) {
    u8 *state = (u8 *)state_data;

#ifndef NON_MATCHING
    register s32 countdown_or_flag ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

    countdown_or_flag = *(s32 *)(state + 0x14);
    countdown_or_flag--;
    *(s32 *)(state + 0x14) = countdown_or_flag;
    if (countdown_or_flag == 0) {
        countdown_or_flag = *(s32 *)(state + 0x1C);
        if (countdown_or_flag != 0) {
            dispatch_result = (u8 *)0x800B0000;
            dispatch_result -= 0x24A4;
        } else {
            dispatch_result = (u8 *)0x800B0000;
            func_800ADB30(state);
            dispatch_result = (u8 *)D_800ADD80;
        }
        *(u8 **)(state - 0x10) = dispatch_result;
    }
#else
    if (--*(s32 *)(state + 0x14) == 0) {
        if (*(s32 *)(state + 0x1C) != 0) {
            /* tail falls through */
        }
        func_800ADB30(state);
        *(void **)(state - 0x10) = D_800ADD80;
    }
#endif
}
