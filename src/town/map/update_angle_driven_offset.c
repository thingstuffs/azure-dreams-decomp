#include "common.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082D58.h"
#include "shared/dungeon_delay_views.h"
#include "engine/node.h"
#include "sdk/libgte.h"
#include "town/map.h"
#include "town/scene/object.h"

   /* arg1 in update_angle_driven_offset */

typedef struct S_800B9D64_2 {
    u8 pad_00[0x66];
    s16 unk_66;
} S_800B9D64_2;   /* ((Rec_D_80082D58 *)arg0)->unk_9C in update_angle_driven_offset */

/* Updates an angle-driven offset and handles inactive objects. */
void update_angle_driven_offset(void *object_arg, DelayMotionZ *offset_state)
{
    Rec_D_80082D58 *object = object_arg;
    s16 angle;
    s16 decay_angle;
    s32 sector;
    s32 phase_value;

    if (*object->unk_98.as_pu8 == 0) {
        unlink_scene_list_node(object_arg);
        unlink_node_if_registered(object);
        (*(u16 *)((u8 *)object + (-2))) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    angle = ((S_800B9D64_2 *)(object->unk_9C))->unk_66;
    sector = angle / 0x200;
    if ((s8)(sector % 4) == object->unk_97) {
        phase_value = rsin((s16)(angle % 0x200) * 2);
        offset_state->unk_08 = -((phase_value >> 4) * 0x1E00);
        object->unk_66 = 30;
        return;
    }

    if (object->unk_66 != 0) {
        s32 offset;
        s32 amplitude;

        object->unk_66 = (u16)object->unk_66 - 3;
        decay_angle = ((S_800B9D64_2 *)(object->unk_9C))->unk_66;
        amplitude = ((rcos((s16)(decay_angle % 0x200) * 0x18) >> 4)
                     * object->unk_66) << 8;
        offset = -amplitude;

        offset_state->unk_08 = offset;
        if (offset > 0) {
            offset_state->unk_08 = amplitude;
            return;
        }
    } else {
        offset_state->unk_08 = 0;
    }
}
