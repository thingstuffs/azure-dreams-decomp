#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801745F0_3 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_801745F0_3;   /* arg0 in func_801745F0 */

typedef struct S_801745F0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801745F0_4;   /* ((S_801745F0_3 *)arg0)->unk_1C in func_801745F0 */


typedef struct S_801745F0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801745F0_0;   /* arg1 in func_801745F0 */


typedef struct S_801745F0_2 {
    u16 unk_00;
} S_801745F0_2;   /* arg0 in func_801745F0; pointer addresses record offset 0x2 */


M2C_UNK func_800478B8();                      /* extern */
extern s32 D_800814A0[3];

void func_801745F0(void *arg0, S_801745F0_0 *arg1, Rec_D_80082E80 *arg2) {
    arg1->unk_02 = (u16) ((S_801745F0_4 *)(((S_801745F0_3 *)arg0)->unk_1C))->unk_02;
    arg1->unk_06 = (u16) ((S_801745F0_4 *)(((S_801745F0_3 *)arg0)->unk_1C))->unk_06;
    arg1->unk_0A = (u16) ((S_801745F0_4 *)(((S_801745F0_3 *)arg0)->unk_1C))->unk_0A;
    func_800478B8(arg2);
    if (arg2->unk_14.at00_u16.v & 0x6000) {
        ((S_801745F0_2 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_801745F0_2 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
