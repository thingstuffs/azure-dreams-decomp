#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800ABB20_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800ABB20_0;   /* arg1 in func_800ABB20 */

typedef struct S_800ABB20_1 {
    u16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
    s16 unk_06;
} S_800ABB20_1;   /* arg0 in func_800ABB20; pointer addresses record offset 0x2 */



extern void func_800478B8(void *arg0);
extern s32 D_800814A0[3];

void func_800ABB20(void *arg0, S_800ABB20_0 *arg1, Rec_D_80082E80 *arg2) {
    u16 temp_v0_3;
    u8 temp_v0;

    arg1->unk_14 = (s32) (arg1->unk_14 + (((S_800ABB20_1 *)((u8 *)arg0 - 0x2))->unk_06 << 0xB));
    ((S_800ABB20_1 *)((u8 *)arg0 - 0x2))->unk_06 = (s16) ((u16) ((S_800ABB20_1 *)((u8 *)arg0 - 0x2))->unk_06 + 1);
    arg1->unk_00 = (s32) (arg1->unk_00 + arg1->unk_0C);
    arg1->unk_04 = (s32) (arg1->unk_04 + arg1->unk_10);
    arg1->unk_08 = (s32) (arg1->unk_08 + arg1->unk_14);
    func_800478B8(arg2);
    temp_v0 = arg2->unk_0C.at00_u8.v;
    if (temp_v0 != 0) {
        temp_v0 = temp_v0 - 0x10;
        arg2->unk_0C.at00_u8.v = temp_v0;
        arg2->unk_0C.at02_u8.v = temp_v0;
        arg2->unk_0C.at01_u8.v = temp_v0;
    }
    temp_v0_3 = ((S_800ABB20_1 *)((u8 *)arg0 - 0x2))->unk_04 - 1;
    ((S_800ABB20_1 *)((u8 *)arg0 - 0x2))->unk_04 = temp_v0_3;
    if ((temp_v0_3 << 0x10) <= 0) {
        ((S_800ABB20_1 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_800ABB20_1 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
}
