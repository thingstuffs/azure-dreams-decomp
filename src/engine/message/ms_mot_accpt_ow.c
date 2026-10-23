#include "common.h"
#include "shared/object_index_slots.h"

#include "common.h"
#include "engine/message.h"

typedef struct {
    s32 unk0;
    void *object;
} ObjectEntry;

extern u8 message_motion_type_a[];
extern u8 message_motion_type_b[];
extern u8 person_motion_tag[];


/* Returns object data for slot 1 or objects with matching type and data tags. */
void *ms_mot_accpt_ow(u8 object_index)
{
    u8 *object;
    void *object_type;
    void *object_data;

    object = object_index_slots[object_index].object;
    if (object == 0) {
        return 0;
    }

    object_data = object + 0x20;
    if (object_index == 1) {
        return object_data;
    }

    object_type = *(void **)(object + 0x10);
    if (object_type == message_motion_type_a || object_type == message_motion_type_b) {
        if (*(void **)((u8 *)object_data + 0x50) == person_motion_tag) {
            return object_data;
        }
    }

    return 0;
}
