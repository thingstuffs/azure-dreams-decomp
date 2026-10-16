#include "common.h"

extern void markSpriteResourcesForPurge(void);
extern void clearMarkedSlotEntries(void);
extern void *prepareUncachedSpriteResource(s16 a0);
extern void drainCdCommandQueue(void);
extern void registerAndUploadThreeSlotSpriteResource(s32 a0, void *a1);
extern void registerAndUploadSpriteResource(s32 a0, void *a1);

/* Initializes an entity by type, running housekeeping first for type 0x38. */
void loadAndUploadSpriteResource(s16 entity_type)
{
    void *entity;

    if (entity_type == 0x38) {
        markSpriteResourcesForPurge();
        clearMarkedSlotEntries();
    }
    entity = prepareUncachedSpriteResource(entity_type);
    if (entity) {
        drainCdCommandQueue();
        if (entity_type == 0x38) {
            registerAndUploadThreeSlotSpriteResource(0x38, entity);
        } else {
            registerAndUploadSpriteResource(entity_type, entity);
        }
    }
}
