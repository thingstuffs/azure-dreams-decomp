#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_800A8440_1 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
} S_800A8440_1;   /* arg0 in func_800A8440; pointer addresses record offset 0x2 */


M2C_UNK func_800478B8();                      /* extern */
extern s32 D_800814A0[];

void func_800A8440(void *arg0, void *arg1, Rec_D_80082E80 *arg2) {
    u16 temp_v0_3;
    u8 temp_v0;
    u8 temp_v0_2;

    func_800478B8(arg2);
    temp_v0 = arg2->unk_0C.at00_u8.v;
    if (temp_v0 != 0) {
        arg2->unk_0C.at00_u8.v = (temp_v0 - 0x10);
        arg2->unk_0C.at02_u8.v = (temp_v0 - 0x10);
        arg2->unk_0C.at01_u8.v = (temp_v0 - 0x10);
    }
    temp_v0_3 = ((S_800A8440_1 *)((u8 *)arg0 - 0x2))->unk_04 - 1;
    ((S_800A8440_1 *)((u8 *)arg0 - 0x2))->unk_04 = temp_v0_3;
    if ((temp_v0_3 << 0x10) <= 0) {
        ((S_800A8440_1 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_800A8440_1 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
