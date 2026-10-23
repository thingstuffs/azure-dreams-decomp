#include "common.h"
#include "shared/object_flags.h"
#include "shared/vector.h"




extern s32 rsin(s32 angle);
extern s32 rcos(s32 angle);
extern s32 check_actor_data_references_match(void *actor);
extern void unlink_node_if_registered(void *object);

/* Computes an offset position from the linked object, flagging failed validation. */
void compute_offset_position_linked_object(void *object, IntVector3 *out_pos)
{
    void *linked_object = *(void **)((u8 *)object + 0x9C);
    IntVector3 *base_pos = *(IntVector3 **)((u8 *)linked_object - 0x18);

    if (check_actor_data_references_match(linked_object) == 0) {
        unlink_node_if_registered(object);
        *(u16 *)((u8 *)object - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    out_pos->x = base_pos->x + rsin(*(s16 *)((u8 *)*(void **)((u8 *)object + 0x9C) + 0x72)) * 0x140;
    out_pos->y = base_pos->y + rcos(*(s16 *)((u8 *)*(void **)((u8 *)object + 0x9C) + 0x72)) * 0x140;
    out_pos->z = base_pos->z + (s32)0xFFE60000;
}
