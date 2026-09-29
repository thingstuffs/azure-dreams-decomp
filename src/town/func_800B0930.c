#include "common.h"

extern void func_800ADB30(void *arg0);
extern void func_800ADB5C(s32 *menu);
extern void func_800ADD80(s32 *menu);

/* Decrement the countdown and select the next dispatch when it expires. */
void func_800AE090(void *state_data) {
    u8 *state = (u8 *)state_data;
    void *handler;

    if (--*(s32 *)(state + 0x14) == 0) {
        if (*(s32 *)(state + 0x1C) != 0) {
            handler = func_800ADB5C;
        } else {
            func_800ADB30(state);
            handler = func_800ADD80;
        }
        *(void **)(state - 0x10) = handler;
    }
}
