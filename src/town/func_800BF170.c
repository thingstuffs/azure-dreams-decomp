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

/* Initializes the object with default data and updates its associated state. */
void func_800BC8D0(void *object, s32 init_arg, Rec_D_80082E80 *state)
{
    s32 *defaults;

    state->unk_14.at00_u16.v |= 0x1C;
    ((S_800BC8D0_1_pre *)object)[-1].unk_00 = D_800BE0D4;
    ((Rec_D_800CFCB4 *)object)->unk_50 = 0;
    ((Rec_D_800CFCB4 *)object)->unk_48 = D_80089634;
    func_8004491C((u8 *)object - 0x20, D_80045340);

    defaults = D_800D20E8;
    ((Rec_D_800CFCB4 *)object)->unk_A0 = defaults[0];
    ((Rec_D_800CFCB4 *)object)->unk_A4 = defaults[1];
    ((Rec_D_800CFCB4 *)object)->unk_A8 = defaults[2];
    func_8008F104(object, init_arg, D_800D20F4);
    func_8003DB94(state, defaults[2], 0);
}
