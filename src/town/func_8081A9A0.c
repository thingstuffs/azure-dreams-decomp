#include "common.h"
#include "m2c_compat.h"

typedef struct S_800249A0_0_pre {
    u16 unk_00;
} S_800249A0_0_pre;   /* the 0x2 bytes before arg0 in func_800249A0, addressed as arg0[-1] */

typedef struct S_800249A0_0 {
    s16 unk_00;
    u8 pad_02[0x2];
    s32 unk_04;
    s16 * unk_08;
    void * unk_0C;
} S_800249A0_0;   /* arg0 in func_800249A0 */

typedef struct S_800249A0_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_800249A0_1;   /* temp_s1 in func_800249A0 */


M2C_UNK func_800537D0();               /* extern */
s32 strlen();                             /* extern */
extern s32 D_800814A0[3];

void func_800249A0(void *arg0) {
    S_800249A0_1 *temp_s1;

    temp_s1 = ((S_800249A0_0 *)arg0)->unk_0C;
    if (((S_800249A0_0 *)arg0)->unk_00 == 0) {
        func_800537D0(*((S_800249A0_0 *)arg0)->unk_08, strlen(((S_800249A0_0 *)arg0)->unk_04), ((S_800249A0_0 *)arg0)->unk_04);
        if (temp_s1->unk_0C & 2) {
            ((S_800249A0_0_pre *)arg0)[-1].unk_00 = (u16) (((S_800249A0_0_pre *)arg0)[-1].unk_00 | 0x8000);
            D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
        }
    }
}
