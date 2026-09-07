#include "common.h"
#include "m2c_compat.h"

typedef struct S_818931B8_0_pre {
    u16 unk_00;
} S_818931B8_0_pre;   /* the 0x2 bytes before arg0 in func_818931B8, addressed as arg0[-1] */

typedef struct S_818931B8_0 {
    void * unk_00;
} S_818931B8_0;   /* arg0 in func_818931B8 */

typedef struct S_818931B8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818931B8_1;   /* temp_v1 in func_818931B8 */

typedef struct S_818931B8_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_818931B8_2;   /* arg1 in func_818931B8 */

typedef struct S_818931B8_3 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818931B8_3;   /* arg2 in func_818931B8 */


M2C_UNK func_800478B8();                      /* extern */
extern s32 D_800814A0[3];

void func_818931B8(void *arg0, S_818931B8_2 *arg1, S_818931B8_3 *arg2) {
    S_818931B8_1 *temp_v1;

    temp_v1 = ((S_818931B8_0 *)arg0)->unk_00;
    temp_v1->unk_14 = (u16) (temp_v1->unk_14 + 1);
    arg1->unk_0A = (u16) (arg1->unk_0A - 4);
    func_800478B8(arg2);
    if (arg2->unk_14 & 0x6000) {
        ((S_818931B8_0_pre *)arg0)[-1].unk_00 = (u16) (((S_818931B8_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
