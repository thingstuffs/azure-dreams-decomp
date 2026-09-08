/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_80033D08();
void func_8003DB94();
void func_800478B8();
M2C_UNK func_8008F134();
M2C_UNK func_8009706C();
s32 func_8009CFE0();
M2C_UNK func_800AAC3C();
s32 func_800C2E1C();
s32 func_800C2F14();
extern s32 D_800814A0[3];


typedef struct S_800AAB20_0_pre {
    u16 unk_00;
} S_800AAB20_0_pre;   /* the 0x2 bytes before arg0 in func_800AAB20, addressed as arg0[-1] */



void func_800AAB20(void *arg0, M2C_UNK arg1, Rec_D_80082E80 *arg2) {
    s32 temp_v0_2;
    s8 *temp_v0;

    if (func_8009CFE0() != 0) {
        func_8008F134(arg0);
        temp_v0 = ((Rec_D_80082D58 *)arg0)->unk_98.as_ps8;
        if (temp_v0 != NULL) {
            *temp_v0 = 0;
        }
        func_80033D08(arg0);
        ((S_800AAB20_0_pre *)arg0)[-1].unk_00 = (u16) (((S_800AAB20_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        return;
    }
    func_8009706C(arg1);
    ((Rec_D_80082D58 *)arg0)->unk_50.as_xcdccad(arg0, arg0, arg1, arg2);
    if (!(((S_800AAB20_0_pre *)arg0)[-1].unk_00 & 0x8000)) {
        temp_v0_2 = func_800C2E1C(((Rec_D_80082D58 *)arg0)->unk_72, ((Rec_D_80082D58 *)arg0)->unk_64);
        if (((Rec_D_80082D58 *)arg0)->unk_74 != temp_v0_2) {
            func_8003DB94(arg2, ((Rec_D_80082D58 *)arg0)->unk_78[temp_v0_2], arg2->unk_04.as_s8);
            ((Rec_D_80082D58 *)arg0)->unk_74 = temp_v0_2;
        }
        if ((func_800C2F14(((Rec_D_80082D58 *)arg0)->unk_72, ((Rec_D_80082D58 *)arg0)->unk_64) << 0x10) != 0) {
            s32 tail_v0;

            tail_v0 = arg2->unk_14.at00_u16.v | 1;
            ASM_TAILSLOT_PIN(tail_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_800AAC3C();
            return;
        }
        arg2->unk_14.at00_u16.v = (u16) (arg2->unk_14.at00_u16.v & 0xFFFE);
        ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_800478B8(arg2);
    }
}
