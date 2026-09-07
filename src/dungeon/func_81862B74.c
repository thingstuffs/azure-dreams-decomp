#include "common.h"
#include "m2c_compat.h"

typedef struct S_81862B74_0_pre {
    u16 unk_00;
} S_81862B74_0_pre;   /* the 0x2 bytes before arg0 in func_81862B74, addressed as arg0[-1] */

typedef struct S_81862B74_0 {
    void * unk_00;
    u16 unk_04;
} S_81862B74_0;   /* arg0 in func_81862B74 */

typedef struct S_81862B74_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81862B74_1;   /* temp_v1 in func_81862B74 */

typedef struct S_81862B74_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81862B74_2;   /* arg2 in func_81862B74 */


M2C_UNK func_8002425C();             /* extern */
M2C_UNK func_800478B8();                      /* extern */
extern s32 D_800814A0[3];

void func_81862B74(void *arg0, M2C_UNK arg1, S_81862B74_2 *arg2) {
    u16 temp_v0;
    S_81862B74_1 *temp_v1;

    temp_v1 = ((S_81862B74_0 *)arg0)->unk_00;
    temp_v1->unk_14 = (u16) (temp_v1->unk_14 + 1);
    func_800478B8(arg2);
    temp_v0 = ((S_81862B74_0 *)arg0)->unk_04 + 1;
    ((S_81862B74_0 *)arg0)->unk_04 = temp_v0;
    if ((s16) temp_v0 == 0xA) {
        func_8002425C(((S_81862B74_0 *)arg0)->unk_00, arg1);
    }
    if (arg2->unk_14 & 0x6000) {
        ((S_81862B74_0_pre *)arg0)[-1].unk_00 = (u16) (((S_81862B74_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
