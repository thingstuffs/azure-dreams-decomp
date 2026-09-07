#include "common.h"
#include "m2c_compat.h"

typedef struct S_80023FF8_0_pre {
    u16 unk_00;
} S_80023FF8_0_pre;   /* the 0x2 bytes before arg0 in func_80023FF8, addressed as arg0[-1] */

typedef struct S_80023FF8_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s16 * unk_08;
    s16 * unk_0C;
} S_80023FF8_0;   /* arg0 in func_80023FF8 */


M2C_UNK func_800537D0();           /* extern */
extern s32 D_800814A0[3];

void func_80023FF8(void *arg0) {
    s16 *temp_s0;

    temp_s0 = ((S_80023FF8_0 *)arg0)->unk_0C;
    func_800537D0(*((S_80023FF8_0 *)arg0)->unk_08, 4, ((S_80023FF8_0 *)arg0)->unk_04 + 7);
    if (*temp_s0 == 0) {
        ((S_80023FF8_0_pre *)arg0)[-1].unk_00 = (u16) (((S_80023FF8_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
