#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80021E88_arg1.h"


typedef struct S_800A2A18_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A2A18_1;   /* arg0 in test_three_axis_box_overlap */

typedef struct S_800A2A18_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A2A18_2;   /* D_80100D20 in test_three_axis_box_overlap */


extern S_800A2A18_2 *town_overlap_origin;

/* Tests whether the offset box overlaps the active collision box on all three axes. */
s32 test_three_axis_box_overlap(S_800A2A18_1 *box, Rec_func_80021E88_arg1 *offset) {
    s32 other_z;
    s32 box_z;
    s32 other_x;
    s32 other_y;
    s32 box_x;
    s32 box_y;

    if (town_overlap_origin != NULL) {
        box_x = offset->unk_00 + box->unk_00;
        other_x = town_overlap_origin->unk_00;
        if ((box_x + box->unk_0C) >= other_x) {
            if ((other_x + town_overlap_origin->unk_0C) >= box_x) {
                box_y = offset->unk_04 + box->unk_04;
                other_y = town_overlap_origin->unk_04;
                if ((box_y + box->unk_10) >= other_y) {
                    if ((other_y + town_overlap_origin->unk_10) >= box_y) {
                        box_z = offset->unk_08 + box->unk_08;
                        other_z = town_overlap_origin->unk_08;
                        if ((box_z + box->unk_14) >= other_z) {
                            if ((other_z + town_overlap_origin->unk_14) >= box_z) {
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
