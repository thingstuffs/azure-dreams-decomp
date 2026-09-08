#include "common.h"

extern u8 *func_80019DFC();
extern s32 func_8001ADE0();
extern u8 D_8001BDB4[16];
extern u8 D_8001C354[16];
extern u8 D_8001E20F[16];

/* Selects context data and overrides it when both event flags are set. */
u8 *func_800182A0(void *context, s32 unused, s32 selector) {
    u8 *selected_data;

    selected_data = func_80019DFC(D_8001BDB4, D_8001C354, context, selector);
    if (func_8001ADE0(0x12C2) != 0) {
        if (func_8001ADE0(*(s16 *)((u8 *)context + 0x18)) != 0) {
            selected_data = D_8001E20F;
        }
    }
    return selected_data;
}
