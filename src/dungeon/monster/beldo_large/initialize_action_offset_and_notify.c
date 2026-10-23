#include "common.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"

extern void equip_item_and_update_status(void *, void *);
extern s16 beldo_large_direction_offsets[];
extern u8 *beldo_script_node;
extern u8 D_80175DBC[];

/* Initializes an offset position and sends a message at action phase three. */
void initialize_action_offset_and_notify(void *action, void *position)
{
    ObjectNodeHeader *object = beldo_script_node;
    u8 *object_position = *(u8 * *)&object->position;
    u8 *object_data = ((u8 *)object) + 0x20;

    if (*(s16 *)((u8 *)action + 0x12) == 0) {
        s16 *direction_offsets = beldo_large_direction_offsets;

        ((s32 *)position)[0] = ((s32 *)object_position)[0];
        ((s32 *)position)[1] = ((s32 *)object_position)[1];
        ((s32 *)position)[2] = ((s32 *)object_position)[2];
        *(u16 *)((u8 *)position + 2) +=
            *(s16 *)((u8 *)direction_offsets +
                     ((*(u16 *)(object_data + 0x2A) >> 7) & 0x1C)) * 6;
        *(u16 *)((u8 *)position + 6) +=
            *(s16 *)((u8 *)direction_offsets +
                     ((*(u16 *)(object_data + 0x2A) >> 7) & 0x1C) + 2) * 6;
    }

    if (*(s16 *)((u8 *)action + 0x12) == 3) {
        u8 *message;

        D_80175DBC[0] = 11;
        message = D_80175DBC;
        message[1] = 15;
        message[2] = 0;
        message[3] = 0;
        equip_item_and_update_status(((u8 *)dungeon_actor_ring_anchor), message);
        ((u16 *)action)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
