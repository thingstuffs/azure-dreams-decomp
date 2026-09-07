#include "common.h"
#include "m2c_compat.h"

typedef struct S_81892BF8_0_pre {
    u16 unk_00;
} S_81892BF8_0_pre;   /* the 0x2 bytes before arg0 in func_81892BF8, addressed as arg0[-1] */

typedef struct S_81892BF8_0 {
    void * unk_00;
    u16 unk_04;
    s16 unk_06;
} S_81892BF8_0;   /* arg0 in func_81892BF8 */

typedef struct S_81892BF8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81892BF8_1;   /* temp_v1 in func_81892BF8 */


extern s32 D_800814A0[3];

void func_81892BF8(void *arg0) {
    u16 temp_v0;
    S_81892BF8_1 *temp_v1;

    temp_v1 = ((S_81892BF8_0 *)arg0)->unk_00;
    temp_v1->unk_14 = (u16) (temp_v1->unk_14 + 1);
    temp_v0 = ((S_81892BF8_0 *)arg0)->unk_04 + 1;
    ((S_81892BF8_0 *)arg0)->unk_04 = temp_v0;
    if ((s16) temp_v0 >= ((S_81892BF8_0 *)arg0)->unk_06) {
        ((S_81892BF8_0_pre *)arg0)[-1].unk_00 = (u16) (((S_81892BF8_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
