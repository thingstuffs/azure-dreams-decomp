#include "common.h"

extern void *getSpriteResourceSlotBuffer(s32 a0);
extern s32 findSpriteResourceSlotById(s32 slot_id);
extern s32 queueSpriteResourceInFreeSlot(s32 a0);
extern void clearMarkedSlotEntries(void);

/* Allocate an unregistered entity's slot, retrying after cleanup if needed; return NULL if already registered. */
void *prepareUncachedSpriteResource(s16 entity_index)
{
    s32 slot_index;
    s32 no_slot = -1;

    slot_index = findSpriteResourceSlotById(entity_index);
    if (slot_index == no_slot) {
        slot_index = queueSpriteResourceInFreeSlot(entity_index);
        if (slot_index == no_slot) {
            clearMarkedSlotEntries();
            slot_index = queueSpriteResourceInFreeSlot(entity_index);
        }
        return getSpriteResourceSlotBuffer(slot_index);
    }
    return 0;
}
