#include "modules/town_door.h"

/* Update the entity step state and switch handlers when the result is zero. */
void townAdvanceDoorStep(void *entity) {
    s16 step_result;
    s32 uninitialized_arg;

    step_result = townCreateObjectsDescendingByCount(entity, *(s32 *)((u8 *)entity + 0x98), uninitialized_arg, *(s16 *)((u8 *)entity
        + 0x90));
    *(s16 *)((u8 *)entity + 0x90) = step_result;
    if ((step_result << 0x10) == 0) {
        *(void **)((u8 *)entity + 0x50) = &townSelectTowerEntryHandlerByItemCount;
    }
}
