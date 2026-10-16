#include "common.h"

extern void markSpriteResourcesForPurge(void);
extern void clearMarkedSlotEntries(void);
extern void *prepareUncachedSpriteResource(s16 a0);
extern s32 Control_CD(s32 a0, void *a1, void *a2);
extern int func_800499DC(int *a0);

/* Gets the code's slot, refreshing for code 0x38, and initializes callback state on success. */
void *beginSpriteResourceLoadWithCompletionFlag(s32 packed_code, s32 *callback_state)
{
    s16 code = (s16)packed_code;
    void *slot;

    if (code == 0x38) {
        markSpriteResourcesForPurge();
        clearMarkedSlotEntries();
    }
    slot = prepareUncachedSpriteResource(code);
    if (slot != 0) {
        *callback_state = 0;
        Control_CD(0xFF, (void *)func_800499DC, callback_state);
    }
    return slot;
}
