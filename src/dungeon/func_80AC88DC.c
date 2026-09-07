#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"


extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, s32, void *, void *);
extern s32 func_800AA6B4(void *, s32, void *, s32);
extern void func_800AA888(void *, s32, void *, void *);
extern void func_801743E8(void *, s32, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_80171728;
extern u8 D_80174E4C[];
extern u8 D_80174E54[];


typedef struct S_801740DC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801740DC_0;   /* arg0 in func_801740DC */


typedef struct S_801740DC_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801740DC_2;   /* counter_base in func_801740DC */


typedef struct S_801740DC_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_801740DC_4;   /* global_base in func_801740DC */


typedef struct S_801740DC_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801740DC_6;   /* counter_base2 in func_801740DC */

void func_801740DC(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    register void *actor ASM_REG("$18") = arg0;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 actor_index ASM_REG("$19") = arg1;   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *target ASM_REG("$17") = arg2;   /* MATCH pin: retail schedule: same instructions, different order without it */
    register void *entity ASM_REG("$16") = arg3;   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 state;
    s32 flags;
    s32 index;
    u8 *global_base;

#define arg0 actor
#define arg1 actor_index
#define arg2 target
#define arg3 entity

    state = ((S_801740DC_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    {
        u8 *counter_base;

        counter_base = (u8 *)&D_80083460;
        ((S_801740DC_2 *)counter_base)->unk_0A--;
    }
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174E4C;
    index = (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(arg2, D_80174E4C[index & 7], 0);
    goto increment_state;

state_one:
    if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v != 0) {
        u8 *counter_base;

        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174E54;
        index = (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9;
        func_80047784(arg2, D_80174E54[index & 7], 0);
        counter_base = (u8 *)&D_80083460;
        ((S_801740DC_2 *)counter_base)->unk_0A++;
        goto increment_state;
    }

    global_base = (u8 *)&D_80083460;
    if (((S_801740DC_4 *)global_base)->unk_02 & 0x1000) {
        goto done;
    }
    ASM_CLOBBER("$4");   /* MATCH pin: retail basic-block layout depends on it */
    ASM_CLOBBER("$5");   /* MATCH pin: retail basic-block layout depends on it */
    ASM_CLOBBER("$6");   /* MATCH pin: retail basic-block layout depends on it */
    if (((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 != 0) {
        if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
            goto done;
        }
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        goto done;
    }
    flags = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32;
    if (flags & 0x100) {
        func_800AA258(arg0, arg1, arg2, arg3);
        goto done;
    }
    if (flags & 0x80000) {
        func_800AA888(arg0, arg1, arg2, arg3);
        func_801743E8(arg0, arg1, arg2, arg3);
        goto done;
    }
    if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 == 0) {
        goto done;
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        if ((func_8009A180(arg3,
                (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(arg3);
    func_800A9A04(arg3);
    if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v == 0) {
        goto done;
    }
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174E54;
    index = (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(arg2, D_80174E54[index & 7], 0);
    ((S_801740DC_4 *)global_base)->unk_0A++;

increment_state:
    ((S_801740DC_0 *)arg0)->unk_9B++;
    goto done;

state_two:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    {
        u8 *counter_base2;

        counter_base2 = (u8 *)&D_80083460;
        ((S_801740DC_6 *)counter_base2)->unk_0A--;
    }
    ((S_801740DC_0 *)arg0)->unk_8C = &D_80171728;

done:
    if (0) {
    }
    return;
}

/* MECHANISM: Four pinned parameter locals, declared in retail emission order, produce the
   0x28 frame and s2/a0, s3/a1, s1/a2 saves while delaying s0/a3 into the branch slot.
   Clobbering incoming a0-a2 at the call-group dominator forces retail's three ABI reload moves. */
