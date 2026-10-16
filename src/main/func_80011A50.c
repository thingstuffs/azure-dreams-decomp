#include "common.h"

typedef struct {
    u8 pad00[0x7C];
    s32 unk7C;
    s32 unk80;
} S_80011A50;

extern u8 D_80083E98;
extern void cardBootFormatSavedSlotDetails(S_80011A50 *record);
extern void cardBootFormatEmptySlotGuidance(S_80011A50 *context);
extern void dungeonBuildATrigonometricTableProcessesUpEightHeightOffsetSegments(S_80011A50 *context);

/* Dispatch to a handler based on the object's table entry and state. */
void cardBootRefreshSlotDetails(S_80011A50 *object)
{
    u8 *entry_table;
    register s32 state;

    entry_table = &D_80083E98;
    if (*(s32 *)(entry_table + (object->unk7C << 7)) != 0) {
        cardBootFormatSavedSlotDetails(object);
        return;
    }
    state = object->unk80;
    if ((state != 0) && (state != 2)) {
        cardBootFormatEmptySlotGuidance(object);
        return;
    }
    dungeonBuildATrigonometricTableProcessesUpEightHeightOffsetSegments(object);
}
