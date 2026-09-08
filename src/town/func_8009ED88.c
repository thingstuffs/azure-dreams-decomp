#include "common.h"
#include "records/Rec_D_800E3D7C.h"


extern s32 func_80033D08();
extern s32 func_80095388();
extern s32 func_8009539C();
extern s16 func_800C2AE8();

extern s32 D_800814A0[3];
extern u8 D_8009C5D8[];


typedef struct S_8009C4E8_0_pre {
    u16 unk_00;
} S_8009C4E8_0_pre;   /* the 0x2 bytes before arg0 in func_8009C4E8, addressed as arg0[-1] */

typedef struct S_8009C4E8_0 {
    u8 pad_00[0x50];
    void * unk_50;
    u8 pad_54[0x18];
    u16 unk_6C;
} S_8009C4E8_0;   /* arg0 in func_8009C4E8 */


typedef struct S_8009C4E8_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_8009C4E8_2;   /* arg2 in func_8009C4E8 */

void func_8009C4E8(void *arg0, Rec_D_800E3D7C *arg1, S_8009C4E8_2 *arg2) {
    s16 value;
    u16 timer;

    timer = ((S_8009C4E8_0 *)arg0)->unk_6C - 1;
    ((S_8009C4E8_0 *)arg0)->unk_6C = timer;
    if ((s16)(timer) < 0) {
        func_80033D08();
        ((S_8009C4E8_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    func_80095388(arg1);
    func_8009539C(arg1);
    value = func_800C2AE8(arg1);
    if (arg1->unk_08.at02_s16.v > value) {
        arg1->unk_08.at02_s16.v = value;
        arg1->unk_0C.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_14.as_s32 = 0;
        arg2->unk_0E = 0x40;
        arg2->unk_0D = 0x40;
        arg2->unk_0C = 0x40;
        arg2->unk_10 = 0x20;
        arg2->unk_14 |= 0x1C;
        ((S_8009C4E8_0 *)arg0)->unk_50 = D_8009C5D8;
    }
}
