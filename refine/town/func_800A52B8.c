#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A2A18_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800A2A18_0;   /* arg1 in func_800A2A18 */

typedef struct S_800A2A18_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A2A18_1;   /* arg0 in func_800A2A18 */

typedef struct S_800A2A18_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A2A18_2;   /* D_80100D20 in func_800A2A18 */


extern S_800A2A18_2 *D_80100D20;

/* Tests whether the offset box overlaps the active collision box on all three axes. */
s32 func_800A2A18(S_800A2A18_1 *box, S_800A2A18_0 *offset) {
    s32 other_z;
    s32 box_z;
    s32 other_x;
    s32 other_y;
    s32 box_x;
    s32 box_y;

    if (D_80100D20 != NULL) {
        box_x = offset->unk_00 + box->unk_00;
        other_x = D_80100D20->unk_00;
        if ((box_x + box->unk_0C) >= other_x) {
            if ((other_x + D_80100D20->unk_0C) >= box_x) {
                box_y = offset->unk_04 + box->unk_04;
                other_y = D_80100D20->unk_04;
                if ((box_y + box->unk_10) >= other_y) {
                    if ((other_y + D_80100D20->unk_10) >= box_y) {
                        box_z = offset->unk_08 + box->unk_08;
                        other_z = D_80100D20->unk_08;
                        if ((box_z + box->unk_14) >= other_z) {
                            if ((other_z + D_80100D20->unk_14) >= box_z) {
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
