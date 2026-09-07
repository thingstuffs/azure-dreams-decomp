#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800BC00C_0 {
    u16 unk_00;
    u8 pad_02[0xC];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x36];
    u16 unk_4A;
    u8 pad_4C[0x2];
    s16 unk_4E;
} S_800BC00C_0;   /* arg0 in func_800BC00C; pointer addresses record offset 0x2 */


typedef struct S_800BC00C_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BC00C_2;   /* arg1 in func_800BC00C */


typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fc;
    s32 f10;
    s32 f14;
} State1;

M2C_UNK func_800478B8();                      /* extern */
s32 func_800BC1C0();               /* extern */
extern s32 func_800BC1C0_state0(void) __asm__("func_800BC1C0");
extern s32 D_800814A0[3];

s32 func_800BC00C(void *arg0, S_800BC00C_2 *arg1, Rec_D_80082E80 *arg2) {
    s16 temp_v1;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v0_2;
    s32 temp_v1_2;
    s32 var_v0;
    s32 state0_v0;
    u16 temp_v0;

    ((S_800BC00C_0 *)((u8 *)arg0 - 0x2))->unk_4A = (u16) (((S_800BC00C_0 *)((u8 *)arg0 - 0x2))->unk_4A - 1);
    func_800478B8(arg2);
    temp_v1 = ((S_800BC00C_0 *)((u8 *)arg0 - 0x2))->unk_4E;
    if (temp_v1 == 1) {
        goto state_1;
    }
    if (temp_v1 >= 2) {
        goto check_ff;
    }
    if (temp_v1 == 0) {
        goto state_0;
    }
    return func_800BC1C0();

check_ff:
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    if (temp_v1 == 0xFF) {
        goto state_ff;
    }
    return func_800BC1C0();

state_0:
    temp_v0 = arg2->unk_1C.at02_u16.v + 0x80;
    arg2->unk_1C.at02_u16.v = temp_v0;
    arg2->unk_1C.at00_u16.v = temp_v0;
    arg2->unk_0C.at00_s32.v = (s32) (arg2->unk_0C.at00_s32.v + 0x80808);
    arg1->unk_02 = (s16) ((u16) arg1->unk_02 + ((s32) (((S_800BC00C_0 *)((u8 *)arg0 - 0x2))->unk_0E - arg1->unk_02) >> 2));
    arg1->unk_06 = (s16) ((u16) arg1->unk_06 + ((s32) (((S_800BC00C_0 *)((u8 *)arg0 - 0x2))->unk_10 - arg1->unk_06) >> 2));
    arg1->unk_0A = (s16) ((u16) arg1->unk_0A + ((s32) (((S_800BC00C_0 *)((u8 *)arg0 - 0x2))->unk_12 - arg1->unk_0A) >> 2));
    state0_v0 = 0xFF;
    if ((s16) ((S_800BC00C_0 *)((u8 *)arg0 - 0x2))->unk_4A > 0) {
        goto state_0_done;
    }
    ((S_800BC00C_0 *)((u8 *)arg0 - 0x2))->unk_4E = state0_v0;
    return func_800BC1C0_state0();
state_0_done:
    return state0_v0;

state_1:
    {
        State1 *p = (State1 *)arg1;
        p->f0 = p->f0 + p->fc;
        p->f4 = p->f4 + p->f10;
        p->f8 = p->f8 + p->f14;
        p->fc = p->fc - (p->fc >> 3);
        p->f10 = p->f10 - (p->f10 >> 3);
        p->f14 = p->f14 - (p->f14 >> 3);
    }
    arg2->unk_0C.at00_s32.v = (s32) (arg2->unk_0C.at00_s32.v + 0xFFF7F7F8);
    temp_v0_2 = 0xFF;
    if ((u8) arg2->unk_0C.at00_s32.v == 0) {
        ((S_800BC00C_0 *)((u8 *)arg0 - 0x2))->unk_4E = temp_v0_2;
        return func_800BC1C0();
    }
    return temp_v0_2;

state_ff:
    ((S_800BC00C_0 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_800BC00C_0 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
    var_v0 = D_800814A0[0] | 0x8000;
    D_800814A0[0] = var_v0;
    return var_v0;
}
