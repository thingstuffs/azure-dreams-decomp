#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800A2DF0_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800A2DF0_0;   /* arg0 in func_800A2DF0 */


/* Add three record increments to the corresponding 16-bit components. */
void func_800A2DF0(S_800A2DF0_0 *components, Rec_D_800E3D7C *increments) {
    components->unk_00 = (u16) (components->unk_00 + increments->unk_00.at02_u16.v);
    components->unk_02 = (u16) (components->unk_02 + increments->unk_04.at02_u16.v);
    components->unk_04 = (u16) (components->unk_04 + increments->unk_08.at02_u16.v);
}
