#include "common.h"
#include "m2c_compat.h"

typedef struct S_80021028_0_pre {
    u16 unk_00;
} S_80021028_0_pre;   /* the 0x2 bytes before arg0 in func_80021028, addressed as arg0[-1] */

typedef struct S_80021028_0 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x6];
    s16 unk_0E;
} S_80021028_0;   /* arg0 in func_80021028 */

typedef struct S_80021028_1 {
    u8 pad_00[0x4];
    u16 unk_04;
    s16 unk_06;
} S_80021028_1;   /* temp_a0 in func_80021028 */


extern s32 D_800814A0[3];

void func_80021028(void *arg0) {
    S_80021028_1 *temp_a0;

    temp_a0 = ((S_80021028_0 *)arg0)->unk_04;
    ((S_80021028_0 *)arg0)->unk_0E = (s16) ((temp_a0->unk_06 * 0xC) + 0x1E);
    if (temp_a0->unk_04 & 0x8000) {
        ((S_80021028_0_pre *)arg0)[-1].unk_00 = (u16) (((S_80021028_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
