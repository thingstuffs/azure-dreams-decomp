#include "common.h"
#include "engine/message/data.h"
#include "shared/object_index_slots.h"
#include "shared/object_node.h"
#include "shared/town_object.h"

#include "engine/message.h"

extern u8 message_motion_type_a[];
extern u8 message_motion_type_b[];

/* Returns object data for slot 1 or objects with matching type and data tags. */
void *ms_mot_accpt_ow(u8 object_index)
{
    ObjectNodeHeader *node;
    void *object_type;
    void *body;

    node = object_index_slots[object_index].object;
    if (node == 0) {
        return 0;
    }

    body = NODE_BODY(node);
    if (object_index == 1) {
        return body;
    }

    object_type = node->update_callback;
    if (object_type == message_motion_type_a || object_type == message_motion_type_b) {
        TownObjectRecord *person = body;
        if (person->unk_50.as_pm == person_motion_tag) {
            return person;
        }
    }

    return 0;
}
