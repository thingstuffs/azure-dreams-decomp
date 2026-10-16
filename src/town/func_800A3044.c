#include "modules/town_door.h"

/* Install the next object handler when the update call succeeds. */
void townInstallNextDoorHandler(void *object, s32 unused_value, s32 update_context, u8 unused_flags) {
    s32 linked_record = *(s32 *)((u8 *)object + 0x98);
    u8 status_byte = *(u8 *)((u8 *)object + 0x94);

    if (townCreateObjectWithSharedData(object, linked_record, update_context, status_byte) != 0) {
        *(s32 *)((u8 *)object + 0x50) = (s32) &townEmitDoorPositionEffect;
    }
}
