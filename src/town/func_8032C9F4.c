#include "common.h"

extern s32 townGetFreeShopSlotCount();
extern void townResolveEntryFlag();
extern s32 townApplyEntryPosition();
extern s32 D_8001BB4C[];
extern s32 D_8001C354;
extern s32 D_8001FAE8[];

/* Processes a request by mode, returning a fallback pointer if the mode 7 check fails. */
s32 townDispatchRequestByMode(s32 request, s32 unused, s32 mode) {
    s32 saved_request = request;
    s32 saved_mode;
    s32 *data_base;
    s32 result;

    saved_mode = mode;
    data_base = D_8001BB4C;
    result = townApplyEntryPosition(data_base, &D_8001C354, saved_request, saved_mode);
    if (saved_mode == 7) {
        if (townGetFreeShopSlotCount() != 0) {
            return result;
        }
        return (s32)D_8001FAE8;
    }
    townResolveEntryFlag(data_base, saved_request, saved_mode);
    return result;
}
