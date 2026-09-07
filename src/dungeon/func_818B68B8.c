#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_818B68B8_0_pre {
    u16 unk_00;
} S_818B68B8_0_pre;   /* the 0x2 bytes before arg0 in func_818B68B8, addressed as arg0[-1] */

typedef struct S_818B68B8_0 {
    void * unk_00;
    u16 unk_04;
} S_818B68B8_0;   /* arg0 in func_818B68B8 */

typedef struct S_818B68B8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818B68B8_1;   /* temp_v1 in func_818B68B8 */

typedef struct S_818B68B8_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_818B68B8_2;   /* arg1 in func_818B68B8 */



M2C_UNK func_800478B8();                      /* extern */
extern s32 D_800814A0[3];

void func_818B68B8(void *arg0, S_818B68B8_2 *arg1, Rec_D_80082E80 *arg2) {
    S_818B68B8_1 *temp_v1;

    temp_v1 = ((S_818B68B8_0 *)arg0)->unk_00;
    temp_v1->unk_14 = (u16) (temp_v1->unk_14 + 1);
    ((S_818B68B8_0 *)arg0)->unk_04 = (u16) (((S_818B68B8_0 *)arg0)->unk_04 + 1);
    arg1->unk_08 = (s32) (arg1->unk_08 + 0xFFF60000);
    func_800478B8(arg2);
    if (arg2->unk_14.at00_u16.v & 0x6000) {
        ((S_818B68B8_0_pre *)arg0)[-1].unk_00 = (u16) (((S_818B68B8_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
