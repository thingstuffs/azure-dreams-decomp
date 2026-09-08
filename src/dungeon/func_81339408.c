#include "common.h"
#include "m2c_compat.h"

extern u8 *D_80175D50[3];
extern u8 D_80083780[12];

/* Return the direction from the reference position to the node position. */
s32 func_80170408(void) {
    s16 *node_pos = *(s16 **)(D_80175D50[0] + 8);
    s16 *ref_pos = (s16 *)D_80083780;
    s16 ref_x = ref_pos[1];
    s16 node_x = node_pos[1];

    if (ref_x < node_x) {
        s16 ref_z = ref_pos[3];
        s16 node_z = node_pos[3];
        if (ref_z < node_z)
            return 1;
        if (node_z < ref_z)
            return 7;
        return 0;
    } else if (node_x < ref_x) {
        s16 ref_z = ref_pos[3];
        s16 node_z = node_pos[3];
        if (ref_z < node_z)
            return 3;
        if (node_z < ref_z)
            return 5;
        return 4;
    } else {
        s16 ref_z = ref_pos[3];
        s16 node_z = node_pos[3];
        s32 direction = 6;
        if (ref_z < node_z)
            return 2;
        if (node_z < ref_z)
            return direction;
        return 0;
    }
}
