#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void drainCdCommandQueue();                            /* extern */
void clearMarkedSlotEntries();                            /* extern */
s32 prepareUncachedSpriteResource();                             /* extern */
void registerAndUploadThreeSlotSpriteResource();                    /* extern */
void markSpriteResourcesForPurge();                            /* extern */

/* Runs cleanup, allocates an entity slot, and starts loading it if available. */
void loadAndUploadThreeSlotSpriteResource(s16 entity_id) {
    s32 entity_slot;

    markSpriteResourcesForPurge();
    clearMarkedSlotEntries();
    entity_slot = prepareUncachedSpriteResource(entity_id);
    if (entity_slot != 0) {
        drainCdCommandQueue();
        registerAndUploadThreeSlotSpriteResource(entity_id, entity_slot);
    }
}
