#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800CFCB4.h"


typedef struct S_800BC8D0_1_pre {
    void * unk_00;
    u8 pad_04[0xC];
} S_800BC8D0_1_pre;   /* the 0x10 bytes before arg0 in func_800BC8D0, addressed as arg0[-1] */




extern void func_8003DB94(void *, s32, s32);
extern void func_8004491C(void *, void *);
extern void func_8008F104(void *, s32, void *);
extern u8 D_80045340[];
extern u8 D_80089634[];
extern u8 D_800BE0D4[];
extern s32 D_800D20E8[];
extern u8 D_800D20F4[];

void func_800BC8D0(void *arg0, s32 arg1, Rec_D_80082E80 *arg2)
{
    s32 *data;

    arg2->unk_14.at00_u16.v |= 0x1C;
    ((S_800BC8D0_1_pre *)arg0)[-1].unk_00 = D_800BE0D4;
    ((Rec_D_800CFCB4 *)arg0)->unk_50 = 0;
    ((Rec_D_800CFCB4 *)arg0)->unk_48 = D_80089634;
    func_8004491C((u8 *)arg0 - 0x20, D_80045340);

    data = D_800D20E8;
    ((Rec_D_800CFCB4 *)arg0)->unk_A0 = data[0];
    ((Rec_D_800CFCB4 *)arg0)->unk_A4 = data[1];
    ((Rec_D_800CFCB4 *)arg0)->unk_A8 = data[2];
    func_8008F104(arg0, arg1, D_800D20F4);
    func_8003DB94(arg2, data[2], 0);
}
