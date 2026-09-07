#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80094984();           /* extern */
extern M2C_UNK D_80091BD8;
extern M2C_UNK D_800D00D0;

typedef struct S_80094130_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
    u8 pad_0C[0x28];
    u16 unk_34;
} S_80094130_0;   /* arg0 in func_80094130 */

typedef struct S_80094130_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80094130_1;   /* arg1 in func_80094130 */

void func_80094130(S_80094130_0 *arg0, S_80094130_1 *arg1) {
    func_80094984(&D_800D00D0, arg0);
    arg0->unk_00 = &D_80091BD8;
    arg0->unk_0A = 5;
    arg0->unk_34 = (u16) arg1->unk_0A;
}
