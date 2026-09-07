#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033D08();                      /* extern */
M2C_UNK func_8008F134();                      /* extern */
M2C_UNK func_800C30A4();                      /* extern */
M2C_UNK func_800C4174();                            /* extern */
extern u8 D_80082660;

typedef struct S_800C4A30_0 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_800C4A30_0;   /* arg0 in func_800C4A30 */

void func_800C4A30(S_800C4A30_0 *arg0) {
    *((arg0->unk_60 * 8) + &D_80082660) = 0;
    func_800C4174();
    func_8008F134(arg0);
    func_80033D08(arg0);
    func_800C30A4(arg0);
}
