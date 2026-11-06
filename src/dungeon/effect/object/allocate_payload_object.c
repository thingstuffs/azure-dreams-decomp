#include "common.h"
#include "dungeon/effect/object.h"
#include "shared/object_node.h"
#include "dungeon/effect.h"

#include "engine/node/allocation.h"                  /* extern */

/* Allocates and initializes an object when the payload value is nonzero. */
void allocate_payload_object(ObjectNodeHeader *owner, s32 payloadValue, s16 payloadShortValue) {
    ObjectNodeHeader *allocatedObject;
    PayloadObjectBody *objectData;

    if (payloadValue != 0) {
        allocatedObject = allocate_list_node(0x210, &owner->next);
        if (allocatedObject != 0) {
            allocatedObject->update_callback = &update_oriented_offset_effect_position;
            objectData = NODE_BODY(allocatedObject);
            objectData->owner = owner;
            objectData->unk_04 = payloadValue;
            objectData->unk_8E.s = payloadShortValue;
        }
    }
}
