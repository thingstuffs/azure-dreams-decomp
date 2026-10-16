#include "common.h"

extern s32 findFreeSpriteResourceSlot(void);
extern void queueSpriteResourceSlotReads(s32 a0, s32 a1);

/* Registers a value in a free slot and returns its index, or -1 if none is free. */
s32 queueSpriteResourceInFreeSlot(s32 value)
{
    s32 slot = findFreeSpriteResourceSlot();

    if (slot != -1) {
        queueSpriteResourceSlotReads(slot, value);
    }
    return slot;
}
