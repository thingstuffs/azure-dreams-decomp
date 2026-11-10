#include "common.h"
#include "engine/node/registration.h"
#include "shared/object_flags.h"
#include "shared/vector.h"
#include "shared/entity.h"
#include "town/person/position.h"
#include "shared/object_node.h"
#include "sdk/libgte.h"

extern s32 check_actor_data_references_match(void *actor);

/* Computes an offset position from the linked object, flagging failed validation. */
void compute_offset_position_linked_object(OwnerFollowingSpriteBody *object, ObjectPosition *out_pos)
{
    void *linked_object = object->linked_object;
    IntVector3 *base_pos = *(IntVector3 **)((u8 *)linked_object - 0x18);

    if (check_actor_data_references_match(linked_object) == 0) {
        unlink_node_if_registered(object);
        NODE_HEADER(object)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    out_pos->x.v = base_pos->x + rsin(*(s16 *)((u8 *)object->linked_object + 0x72)) * 0x140;
    out_pos->y.v = base_pos->y + rcos(*(s16 *)((u8 *)object->linked_object + 0x72)) * 0x140;
    out_pos->z.v = base_pos->z + (s32)0xFFE60000;
}
