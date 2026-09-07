#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800A48B0_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800A48B0_0;   /* arg0 in func_800A48B0 */


void func_800A48B0(S_800A48B0_0 *arg0, Rec_D_800E3D7C *arg1) {
    arg0->unk_00 = (s32) arg1->unk_00.at00_s32.v;
    arg0->unk_04 = (s32) arg1->unk_04.at00_s32.v;
    arg0->unk_08 = (s32) arg1->unk_08.at00_s32.v;
    arg0->unk_0C = (s32) arg1->unk_0C.as_s32;
    arg0->unk_10 = (s32) arg1->unk_10.at00_s32.v;
    arg0->unk_14 = (s32) arg1->unk_14.as_s32;
}
