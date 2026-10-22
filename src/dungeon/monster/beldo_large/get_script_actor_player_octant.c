#include "common.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "m2c_compat.h"

extern u8 *beldo_actor_nodes[3];

/* Return the direction from the reference position to the node position. */
s32 get_script_actor_player_octant(void) {
    s16 *node_pos = *(s16 * *)&((ObjectNodeHeader *)beldo_actor_nodes[0])->position;
    s16 ref_x = view_reference_entity.x.w.i;
    s16 node_x = node_pos[1];

    if (ref_x < node_x) {
        s16 ref_z = view_reference_entity.y.w.i;
        s16 node_z = node_pos[3];
        if (ref_z < node_z)
            return 1;
        if (node_z < ref_z)
            return 7;
        return 0;
    } else if (node_x < ref_x) {
        s16 ref_z = view_reference_entity.y.w.i;
        s16 node_z = node_pos[3];
        if (ref_z < node_z)
            return 3;
        if (node_z < ref_z)
            return 5;
        return 4;
    } else {
        s16 ref_z = view_reference_entity.y.w.i;
        s16 node_z = node_pos[3];
        s32 direction = 6;
        if (ref_z < node_z)
            return 2;
        if (node_z < ref_z)
            return direction;
        return 0;
    }
}
