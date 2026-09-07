#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800A2DF0_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800A2DF0_0;   /* arg0 in func_800A2DF0 */


void func_800A2DF0(S_800A2DF0_0 *arg0, Rec_D_800E3D7C *arg1) {
    arg0->unk_00 = (u16) (arg0->unk_00 + arg1->unk_00.at02_u16.v);
    arg0->unk_02 = (u16) (arg0->unk_02 + arg1->unk_04.at02_u16.v);
    arg0->unk_04 = (u16) (arg0->unk_04 + arg1->unk_08.at02_u16.v);
}
