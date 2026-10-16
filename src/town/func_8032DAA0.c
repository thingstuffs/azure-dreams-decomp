#include "common.h"

extern u8 *townApplyEntryPosition();
extern s32 townGetScriptFlagMask();
extern u8 D_8001BDB4[16];
extern u8 D_8001C354[16];
extern u8 D_8001E20F[16];

/* Selects context data and overrides it when both event flags are set. */
u8 *townSelectContextDataWithFlagOverride(void *context, s32 unused, s32 selector) {
    u8 *selected_data;

    selected_data = townApplyEntryPosition(D_8001BDB4, D_8001C354, context, selector);
    if (townGetScriptFlagMask(0x12C2) != 0) {
        if (townGetScriptFlagMask(*(s16 *)((u8 *)context + 0x18)) != 0) {
            selected_data = D_8001E20F;
        }
    }
    return selected_data;
}
