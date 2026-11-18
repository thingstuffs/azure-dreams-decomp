#include "common.h"
#include "shared/entity.h"
#include "town/menu.h"
#include "town/player/fallback_handler_position_g00541.h"

/* Tests whether the offset box overlaps the active collision box on all three axes. */
s32 test_three_axis_box_overlap(struct S_800A2A18_1 *box, ObjectPosition *offset) {
    s32 other_z;
    s32 box_z;
    s32 other_x;
    s32 other_y;
    s32 box_x;
    s32 box_y;

    if (town_overlap_origin != NULL) {
        box_x = offset->x.v + box->x;
        other_x = town_overlap_origin->x;
        if ((box_x + box->extent_x) >= other_x) {
            if ((other_x + town_overlap_origin->extent_x) >= box_x) {
                box_y = offset->y.v + box->y;
                other_y = town_overlap_origin->y;
                if ((box_y + box->extent_y) >= other_y) {
                    if ((other_y + town_overlap_origin->extent_y) >= box_y) {
                        box_z = offset->z.v + box->z;
                        other_z = town_overlap_origin->z;
                        if ((box_z + box->extent_z) >= other_z) {
                            if ((other_z + town_overlap_origin->extent_z) >= box_z) {
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
