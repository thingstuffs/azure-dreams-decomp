#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C8600_1 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800C8600_1;   /* arg0 in func_800C8600 */

typedef struct S_800C8600_2 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_800C8600_2;   /* ((S_800C8600_1 *)arg0)->unk_80 in func_800C8600 */




/* extern */
extern u8 D_80082660;
extern M2C_UNK D_800D62C4;

typedef struct S_800C8600_0 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_800C8600_0;   /* arg0 in func_800C8600 */


M2C_UNK func_800C4174(S_800C8600_0 *, M2C_UNK, M2C_UNK);
void func_800C8600(S_800C8600_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    ((S_800C8600_2 *)(((S_800C8600_1 *)arg0)->unk_80))->unk_04 = &D_800D62C4;
    *((arg0->unk_60 * 8) + &D_80082660) = 0;
    func_800C4174(arg0, arg1, arg2);
}
