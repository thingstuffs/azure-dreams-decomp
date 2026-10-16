#include "common.h"

extern void townInitializeItemMenuRecordFields(s32 objectData, s32 owner, s32 listConfig, s32 entryCount, s32 entryIds);
extern void townInitializeItemMenuLinkedRecordVectors(s32 objectData, s32 dataC8, s32 dataA0, s32 dataB0, s32 x, s32 y);
extern void townInitializeItemMenuListEntries(s32 objectData);

/* Initialize a list object's configuration, position, and display entries. */
void townInitializeItemMenuListDisplay(s32 objectData, s32 owner, s32 listConfig, s32 entryCount, s32 x, s32 y, s32 entryIds) {
    townInitializeItemMenuRecordFields(objectData, owner, listConfig, entryCount, entryIds);
    townInitializeItemMenuLinkedRecordVectors(objectData, objectData + 0xC8, objectData + 0xA0, objectData + 0xB0, x, y);
    townInitializeItemMenuListEntries(objectData);
}
