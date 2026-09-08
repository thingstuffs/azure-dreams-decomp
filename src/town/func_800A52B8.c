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

s32 func_800A2A18(S_800A2A18_1 *arg0, Rec_func_80021E88_arg1 *arg1) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a3;
    s32 temp_a3_2;
    s32 temp_v1;
    s32 temp_v1_2;

    if (D_80100D20 != NULL) {
        temp_v1 = arg1->unk_00 + arg0->unk_00;
        temp_a3 = D_80100D20->unk_00;
        if ((temp_v1 + arg0->unk_0C) >= temp_a3) {
            if ((temp_a3 + D_80100D20->unk_0C) >= temp_v1) {
                temp_v1_2 = arg1->unk_04 + arg0->unk_04;
                temp_a3_2 = D_80100D20->unk_04;
                if ((temp_v1_2 + arg0->unk_10) >= temp_a3_2) {
                    if ((temp_a3_2 + D_80100D20->unk_10) >= temp_v1_2) {
                        temp_a1 = arg1->unk_08 + arg0->unk_08;
                        temp_a0 = D_80100D20->unk_08;
                        if ((temp_a1 + arg0->unk_14) >= temp_a0) {
                            if ((temp_a0 + D_80100D20->unk_14) >= temp_a1) {
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

/* MECHANISM: Frameless leaf with one loaded collision-box pointer and block-local
   axis sums/bounds. Nested positive tests share one terminal zero-return edge. */
