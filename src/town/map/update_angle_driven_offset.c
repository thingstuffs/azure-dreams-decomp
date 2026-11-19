#include "common.h"
#include "shared/object_flags.h"
#include "town/map/effect.h"
#include "shared/object_node.h"
#include "shared/dungeon_delay_views.h"
#include "engine/node.h"
#include "sdk/libgte.h"
#include "town/map.h"
#include "town/scene/object.h"

   /* arg1 in update_angle_driven_offset */


/* Updates an angle-driven offset and handles inactive objects. */
void update_angle_driven_offset(void *object_arg, ObjectPosition *offset_state)
{
    MapParticleEffect *effect = object_arg;
    s16 angle;
    s16 decay_angle;
    s32 sector;
    s32 phase_value;

    if (*effect->active_flag == 0) {
        unlink_scene_list_node(object_arg);
        unlink_node_if_registered(object_arg);
        NODE_HEADER(object_arg)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    angle = effect->parent->angle;
    sector = angle / 0x200;
    if ((s8)(sector % 4) == effect->index) {
        phase_value = rsin((s16)(angle % 0x200) * 2);
        offset_state->z.v = -((phase_value >> 4) * 0x1E00);
        effect->angle = 30;
        return;
    }

    if (effect->angle != 0) {
        s32 offset;
        s32 amplitude;

        effect->angle = (u16)effect->angle - 3;
        decay_angle = effect->parent->angle;
        amplitude = ((rcos((s16)(decay_angle % 0x200) * 0x18) >> 4)
                     * effect->angle) << 8;
        offset = -amplitude;

        offset_state->z.v = offset;
        if (offset > 0) {
            offset_state->z.v = amplitude;
            return;
        }
    } else {
        offset_state->z.v = 0;
    }
}
