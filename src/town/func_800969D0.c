#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80094984();           /* extern */
extern M2C_UNK D_80091BD8;
extern M2C_UNK D_800D00D0;


typedef struct S_80094130_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80094130_1;   /* arg1 in func_80094130 */

void func_80094130(Rec_func_80094268_arg0 *arg0, S_80094130_1 *arg1) {
    func_80094984(&D_800D00D0, arg0);
    arg0->unk_00.as_pm = &D_80091BD8;
    arg0->unk_0A.as_s16 = 5;
    arg0->unk_34.as_u16 = (u16) arg1->unk_0A;
}
