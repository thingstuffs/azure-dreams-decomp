#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AAE98_arg0.h"
#include "records/Rec_func_800AB014_arg0.h"

s32 func_800AAE98();                          /* extern */
M2C_UNK func_800AAFE0();          /* extern */
M2C_UNK func_800AB014();             /* extern */
s32 func_800AB030();                          /* extern */
extern M2C_UNK D_800AB5C0;

typedef struct {
    s16 unk0;
    u16 value;
} LocalEntry;



void func_800AB708(Rec_func_800AB014_arg0 *arg0, Rec_func_800AAE98_arg0 *arg1) {
    LocalEntry sp10[6];
    void *call_arg;
    register s32 call_result ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 temp_s0;
    u16 stack_value;

    func_800AAFE0(sp10, 4);
    call_result = func_800AAE98(arg1);
    ASM_KEEP(call_result);   /* MATCH pin: retail schedule: same instructions, different order without it */
    call_arg = arg0;
    ASM_KEEP(call_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_s0 = call_result;
    call_result = func_800AB030(call_arg);
    stack_value = sp10[2].value;
    temp_s0 += call_result;
    sp10[2].value = stack_value - temp_s0;
    arg1->unk_02 = (s16) ((s32) (arg1->unk_02 + (s16) sp10[0].value) / 2);
    arg1->unk_06 = (s16) ((s32) (arg1->unk_06 + (s16) sp10[1].value) / 2);
    arg1->unk_0A = (s16) ((s32) (arg1->unk_0A + (s16) sp10[2].value) / 2);
    func_800AB014(arg0, 4);
    if (arg0->unk_90 >= 0x64) {
        arg0->unk_50 = &D_800AB5C0;
        arg0->unk_72.as_s16 = 0;
        arg0->unk_6C = 0xA;
    }
}

/* MECHANISM: A six-entry 4-byte sibling array creates the 24-byte stack object and exact 0x38 frame.
   Guarded $v0/$a0 ABI pins place the first return save in the second call's delay slot.
   A named u16 RMW value yields lhu-v1/subu/sh, and 2.7.2-cdk-G0 fills the final branch with the lui. */
